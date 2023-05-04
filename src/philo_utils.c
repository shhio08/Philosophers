/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:37:05 by stakimot          #+#    #+#             */
/*   Updated: 2023/05/04 19:37:45 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	have_fork(t_philo *philo)
{
	if (philo->philo_number % 2 == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		printf("%ld %d has taken a fork\n",
			get_now_time() - philo->info->start, philo->philo_number);
		pthread_mutex_lock(philo->r_fork);
		printf("%ld %d has taken a fork\n",
			get_now_time() - philo->info->start, philo->philo_number);
	}
	else
	{
		usleep(50);
		pthread_mutex_lock(philo->r_fork);
		printf("%ld %d has taken a fork\n",
			get_now_time() - philo->info->start, philo->philo_number);
		usleep(50);
		pthread_mutex_lock(philo->l_fork);
		printf("%ld %d has taken a fork\n",
			get_now_time() - philo->info->start, philo->philo_number);
	}
}

void	happy_eat(t_philo *philo)
{
	printf("%ld %d is eating\n",
		get_now_time() - philo->info->start, philo->philo_number);
	my_usleep(philo->info->eat);
	if (philo->philo_number % 2 == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	pthread_mutex_lock(&philo->info->check_die);
	philo->last_eat = get_now_time();
	pthread_mutex_unlock(&philo->info->check_die);
	philo->eat_cnt++;
}

void	happy_think(t_philo *philo)
{
	printf("%ld %d is thinking\n",
		get_now_time() - philo->info->start, philo->philo_number);
}

void	happy_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n",
		get_now_time() - philo->info->start, philo->philo_number);
	my_usleep(philo->info->sleep);
}
