/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 00:23:54 by abaudot           #+#    #+#             */
/*   Updated: 2021/07/16 18:50:29 by aime             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	ft_isnum(char *str)
{
	while (*str)
	{
		if ((unsigned int)(*str - '0') > 9)
			return (0);
		++str;
	}
	return (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}
