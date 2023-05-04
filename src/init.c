/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:34:23 by stakimot          #+#    #+#             */
/*   Updated: 2023/05/04 19:35:14 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_info	*init_info(int argc, char **argv)
{
	t_info	*info;
	int		cnt;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->menbers = ft_atoi(argv[1]);
	info->die = ft_atoi(argv[2]);
	info->eat = ft_atoi(argv[3]);
	info->sleep = ft_atoi(argv[4]);
	info->check = false;
	info->full = false;
	info->full_menbers = 0;
	if (argc == 6)
		info->must_eat = ft_atoi(argv[5]);
	else
		info->must_eat = 0;
	pthread_mutex_init(&info->check_die, NULL);
	pthread_mutex_init(&info->check_full, NULL);
	info->fork = (pthread_mutex_t *)malloc
		(sizeof(pthread_mutex_t) * info->menbers);
	if (!info->fork)
		return (NULL);
	cnt = 0;
	while (cnt <= info->menbers)
		pthread_mutex_init(&info->fork[cnt++], NULL);
	return (info);
}

t_philo	*init_philo(t_info *info)
{
	t_philo	*philo;
	int		cnt;

	cnt = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * info->menbers);
	if (!philo)
		return (NULL);
	while (cnt < info->menbers)
	{
		philo[cnt].info = info;
		philo[cnt].philo_number = cnt;
		philo[cnt].l_fork = &info->fork[cnt];
		philo[cnt].last_eat = get_now_time();
		philo[cnt].eat_cnt = 0;
		if (cnt == info->menbers - 1)
			philo[cnt].r_fork = &info->fork[0];
		else
			philo[cnt].r_fork = &info->fork[(cnt + 1)];
		cnt++;
	}
	return (philo);
}