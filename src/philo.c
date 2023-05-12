/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:35:55 by stakimot          #+#    #+#             */
/*   Updated: 2023/05/12 16:56:34 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	move_check(t_philo *philo)
{
	bool	check;
	bool	full;

	pthread_mutex_lock(&philo->info->check_die);
	check = philo->info->check;
	pthread_mutex_unlock(&philo->info->check_die);
	if (check == true)
	{
		printf("%ld %d died\n",
			get_now_time() - philo->info->start, philo->philo_number);
		return (true);
	}
	if (philo->info->must_eat != 0 && philo->eat_cnt == philo->info->must_eat)
	{
		pthread_mutex_lock(&philo->info->check_full);
		philo->info->full_menbers++;
		pthread_mutex_unlock(&philo->info->check_full);
	}
	pthread_mutex_lock(&philo->info->check_full);
	full = philo->info->full;
	pthread_mutex_unlock(&philo->info->check_full);
	if (full == true)
		return (true);
	return (false);
}

void	*philo_move(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
	{
		have_fork(philo);
		// if (move_check(philo))
		// 	break ;
		happy_eat(philo);
		if (move_check(philo))
			break ;
		happy_sleep(philo);
		if (move_check(philo))
			break ;
		happy_think(philo);
		if (move_check(philo))
			break ;
	}
	return (NULL);
}
