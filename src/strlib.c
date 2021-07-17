/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 00:23:54 by abaudot           #+#    #+#             */
/*   Updated: 2021/07/17 02:02:09 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_atoi(const char *str)
{
	int	res;

	res = 0;
	while (*str)
	{
		res = res * 10 + (*str - '0');
		++str;
	}
	return (res);
}

char	ft_isnum(const char *str)
{
	while (*str)
	{
		if ((unsigned int)(*str - '0') > 9)
			return (0);
		++str;
	}
	return (1);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

void	ft_putunbr(unsigned int n)
{
	char		buf[12];
	int			i;

	i = 11;
	buf[11] = 0;
	if (n == 0)
		buf[--i] = '0';
	while (n)
	{
		buf[--i] = '0' + (n % 10);
		n /= 10;
	}
	write(1, buf + i, 11 - i);
}
