/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:51:13 by stakimot          #+#    #+#             */
/*   Updated: 2023/04/27 11:54:43 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_long(long num, char c, int minus)
{
	if (LONG_MAX / 10 < num && c && !minus)
		return (1);
	if (LONG_MAX / 10 == num && LONG_MAX % 10 < c - '0' && !minus)
		return (1);
	if (LONG_MIN / 10 > -num && c && minus)
		return (-1);
	if (LONG_MIN / 10 == -num && LONG_MIN % 10 > -(c - '0') && minus)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	num;
	size_t	cnt;
	int		minus;

	num = 0;
	cnt = 0;
	minus = 0;
	while ((str[cnt] >= '\t' && str[cnt] <= '\r') || str[cnt] == ' ')
		cnt++;
	if (str[cnt] == '+' || str[cnt] == '-')
	{
		if (str[cnt++] == '-')
			minus++;
	}
	while (str[cnt] >= '0' && str[cnt] <= '9')
	{
		num = num * 10 + (str[cnt++] - '0');
		if (check_long(num, str[cnt], minus) > 0)
			return ((int)LONG_MAX);
		if (check_long(num, str[cnt], minus) < 0)
			return ((int)LONG_MIN);
	}
	if (minus)
		num *= -1;
	return ((int)num);
}
