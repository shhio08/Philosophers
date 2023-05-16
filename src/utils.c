/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:39:27 by stakimot          #+#    #+#             */
/*   Updated: 2023/05/16 16:39:42 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_now_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	my_usleep(int num)
{
	long	time;

	time = get_now_time();
	while (get_now_time() < time + (long)num)
		usleep(100);
}

void	print_move(t_philo *philo, t_now move)
{
	pthread_mutex_lock(&philo->info->check_die);
	pthread_mutex_lock(&philo->info->check_full);
	if (philo->info->check == true || philo->info->full == true)
		return ;
	pthread_mutex_unlock(&philo->info->check_die);
	pthread_mutex_unlock(&philo->info->check_full);
	if (move == TAKEN_FORK)
	{
		printf("%ld %d has taken a fork\n",
			get_now_time() - philo->info->start, philo->philo_number);
	}
	else if (move == EAT)
	{
		printf("%ld %d is eating\n",
			get_now_time() - philo->info->start, philo->philo_number);
	}
	else if (move == THINK)
	{
		printf("%ld %d is thinking\n",
			get_now_time() - philo->info->start, philo->philo_number);
	}
	else if (move == SLEEP)
	{
		printf("%ld %d is sleeping\n",
			get_now_time() - philo->info->start, philo->philo_number);
	}
}
