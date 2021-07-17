/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:16:15 by abaudot           #+#    #+#             */
/*   Updated: 2021/07/17 02:55:50 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
** Classic buffer;
** flush at the end of the string or when it's full
*/
static void	buffer_(const char c)
{
	static int		i = 0;
	static char		buffer[BUFFER_SIZE + 1];

	if (!c || i == BUFFER_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	else
	{
		buffer[i] = c;
		++i;
	}
}

/*
** signal handler;
** @Object:	use signals as bits and use bits to construct
** 								a char, then add the char to the buffer.
** 43:		SIGUSR1 is bit 1 SIGUSR2 is bit 0, add the bit to de char bit chain
** 46-52:	if the chain is complete (8 bits) append the char to the buffer
**			send message to the client to notify him that a char have been
**			proprely recived
** 53-60:	make space for the next bit and send signal for the next bits
*/
static void	handler(int signum, siginfo_t *info, void *context)
{
	static uint8_t	c = 0x0;
	static int		bit = 0;

	(void)context;
	c |= (signum == SIGUSR1);
	++bit;
	if (bit == 8)
	{
		bit = 0;
		buffer_(c);
		c = 0x0;
		kill(info->si_pid, SIGUSR1);
	}
	else
	{
		c <<= 1;
		kill(info->si_pid, SIGUSR2);
	}
}

/*
** Server main;
** @Object:	capture SIGUSR1 and SIGUSR2 signal
** 63:		output the Server PID NUM
** 64-67:	setup sigaction struct
** wait
*/
int	main(void)
{
	struct sigaction	sa_signal;	

	printf("\033[34;1mPID:\t\033[1;31m[%d]\033[0;0m\n", getpid());
	sigemptyset(&sa_signal.sa_mask);
	sa_signal.sa_flags = SA_SIGINFO;
	sa_signal.sa_handler = NULL;
	sa_signal.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);
	while (1)
		pause();
	return (0);
}
