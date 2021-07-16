/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:28:44 by abaudot           #+#    #+#             */
/*   Updated: 2021/07/16 18:59:54 by aime             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
**	Whe are at the end of the string, Only send 0 bit to the server
*/
static void	end_of_connection(const pid_t pid)
{
	static int	bit = 0;

	if (bit == 8)
		exit(0);
	++bit;
	kill(pid, SIGUSR2);
	write(1,"\n", 1);
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
static void	send_bit(char *s, const pid_t pid)
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
		 kill(server_pid, SIGUSR1);
	else
		 kill(server_pid, SIGUSR2);
}

/*
** signal handler
** @Object: acknowledge that the signal have been recived by the server
**			and send the new one (calling send_bit)
*/
static void	handler(int signum, siginfo_t *info, void * context)
{
	(void)info;
	(void)context;
	if (signum == SIGUSR1)
		write(1, "*", 1);
	send_bit(0, 0);
}

int	main(int ac, char **av)
{
	int					server_pid;
	struct sigaction	sa_signal;	

	if (ac != 3 || !ft_isnum(av[1]))
	{
		printf ("\033[34;1mClient:\033[1;31m\tInvalide format.\n");
		printf ("\033[1;35mUsage:\033[0;0m\t./client <Server_PID> <Message>.\n");
		return (1);
	}
	server_pid = ft_atoi(av[1]);
	sigemptyset(&sa_signal.sa_mask);
	sa_signal.sa_flags = SA_SIGINFO;
	sa_signal.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);
	send_bit(av[2], server_pid);
	while(1)
		pause();
	return (0);
}
