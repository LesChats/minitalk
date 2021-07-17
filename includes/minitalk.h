/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 00:25:35 by abaudot           #+#    #+#             */
/*   Updated: 2021/07/17 02:04:31 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdint.h>

# define BUFFER_SIZE 10000

int		ft_atoi(const char *str);
char	ft_isnum(const char *str);
int		ft_strlen(const char *str);
void	ft_putunbr(unsigned int n);
#endif
