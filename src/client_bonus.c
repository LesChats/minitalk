/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:28:44 by abaudot           #+#    #+#             */
/*   Updated: 2021/07/25 13:08:48 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
**	Whe are at the end of the string, Only send 0 bit to the server
*/
static int	end_of_connection(const pid_t pid)
{
	static int	bit = 0;

	if (bit == 8)
	{
		write(1, "\n", 1);
		exit(0);
	}
	++bit;
	kill(pid, SIGUSR2);
	return (0);
}

/*
** @object:	Send the string to the server bit after bit
**			using SIGUSR1 as 1 ans SIGUSR2 as 0
**			then wait for the server to notify reception for sending the next
** 42-47:	First call, init working string, server_pid, and first character
** 48-51:	The caracter have been send, were going for the next one
** 57:		We'v hit the last characters (0) send it quicly to the server
**			(call end_of_connection)
**
**	Check the bit and seend SIGUSR1 or SIGUSR2 accordingly
*/
static int	send_bit(char *s, const pid_t pid)
{
	static int		bit = 8;
	static uint8_t	c = 0x0;
	static char		*string = 0;
	static pid_t	server_pid;

	if (!string)
	{
		string = s;
		c = *string;
		server_pid = pid;
	}
	if (bit == 0)
	{
		bit = 8;
		c = *(++string);
	}
	if (!c)
		return (end_of_connection(server_pid));
	--bit;
	if ((c >> bit) & 0x1)
		 return (kill(server_pid, SIGUSR1));
	return (kill(server_pid, SIGUSR2));
}

/*
** signal handler
** @Object: acknowledge that the signal have been recived by the server
**			and send the new one (calling send_bit)
*/
static void	handler(int signum, siginfo_t *info, void *context)
{
	static unsigned int	count;

	(void)info;
	(void)context;
	if (signum == SIGUSR1)
	{
		write(1, "\r\033[1;32mRecived: \033[0;0m", 17);
		ft_putunbr(++count);
		write(1, " \033[1;33mBytes\033[0;0m", 13);
	}
	send_bit(0, 0);
}

int	main(int ac, char **av)
{
	struct sigaction	sa_signal;	

	if (ac != 3 || !ft_isnum(av[1]))
	{
		printf ("\033[1;34mClient:\033[1;31m\tInvalide format.\n");
		printf ("\033[1;35mUsage:\033[0;0m\t./client <\033[1;32m Server_PID");
		printf ("\033[0;0m> <\033[1;33mMessage\033[0;0m>.\n");
		return (1);
	}
	sigemptyset(&sa_signal.sa_mask);
	sa_signal.sa_flags = SA_SIGINFO;
	sa_signal.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);
	printf("\033[1;34mSending:");
	printf("\033[1;32m %d \033[1;31mBytes\033[0;0m..\n", ft_strlen(av[2]) + 1);
	if (send_bit(av[2], ft_atoi(av[1])))
	{
		printf("\033[1;31mError:\033[0;0m No Server found\n");
		exit(0);
	}
	while (1)
		pause();
	return (0);
}
