/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:28:44 by abaudot           #+#    #+#             */
/*   Updated: 2021/07/15 00:26:20 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int ac, char **av)
{
	int	server_pid;

	if (ac != 3 || !ft_isnum(av[1]))
	{
		printf ("Client:\tInvalide format.\n");
		printf ("Usage:\t./client <Server_PID> <Message>.\n");
		return (1);
	}
	server_pid = ft_atoi(av[1]);
	printf("send message to %d\n", server_pid);
	int i = kill(server_pid, SIGUSR1);
	printf("relust %d\n", i);

	return (0);
}
