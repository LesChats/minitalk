/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:16:15 by abaudot           #+#    #+#             */
/*   Updated: 2021/07/15 01:19:55 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler_sigusr(int signum, siginfo_t *info, void * context)
{
	(void)context;
	(void)info;
	printf("signal %d has been received.\n", signum);
}

int main(void)
{
	struct sigaction	sa_signal;	
	const pid_t server_pid = getpid();

	printf("PID:\t%d\n", server_pid);
	sigemptyset(&sa_signal.sa_mask);
	sigaddset(&sa_signal.sa_mask, SIGINT);
	sigaddset(&sa_signal.sa_mask, SIGQUIT);
	sa_signal.sa_handler = NULL;
	sa_signal.sa_sigaction = handler_sigusr;
	sigaction(SIGUSR1, &sa_signal, NULL);
	pause();
	return (0);
}

