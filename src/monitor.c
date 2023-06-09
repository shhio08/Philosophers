/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:38:34 by stakimot          #+#    #+#             */
/*   Updated: 2023/05/30 21:01:48 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	check_die(t_info *info)
{
	int		cnt;
	long	last_eat;

	cnt = 0;
	while (cnt < info->menbers)
	{
		pthread_mutex_lock(&info->check_die);
		last_eat = info->philo[cnt++].last_eat;
		if (get_now_time() - last_eat > info->die)
		{
			info->check = true;
			printf("%ld %d died\n",
				get_now_time() - info->start, info->philo[cnt].philo_number);
			pthread_mutex_unlock(&info->check_die);
			return (true);
		}
		pthread_mutex_unlock(&info->check_die);
	}
	return (false);
}

static bool	check_full(t_info *info)
{
	int	full_menbers;

	if (info->must_eat == 0)
		return (false);
	pthread_mutex_lock(&info->check_full);
	full_menbers = info->full_menbers;
	pthread_mutex_unlock(&info->check_full);
	if (full_menbers >= info->menbers)
	{
		pthread_mutex_lock(&info->check_full);
		info->full = true;
		pthread_mutex_unlock(&info->check_full);
		return (true);
	}
	return (false);
}

void	monitoring(t_info *info)
{
	if (info->menbers == 1)
		return ;
	while (1)
	{
		if (check_die(info))
			break ;
		if (check_full(info))
			break ;
		my_usleep(5);
	}
}
