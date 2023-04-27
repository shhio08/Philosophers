/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:52:09 by stakimot          #+#    #+#             */
/*   Updated: 2023/04/27 13:40:10 by stakimot         ###   ########.fr       */
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
	if (argc == 6)
		info->must_eat = ft_atoi(argv[5]);
	else
		info->must_eat = -1;
	info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->menbers);
	if (!info->fork)
		return (NULL);
	cnt = 0;
	while (cnt <= info->menbers)
		pthread_mutex_init(&info->fork[cnt++], NULL);
	return (info);
}

void	init_philo(t_info *info, t_philo *philo)
{
	int	cnt;

	cnt = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * info->menbers);
	if (!philo)
		return ;
	while (cnt < info->menbers)
	{
		philo[cnt].info = info;
		philo[cnt].philo_number = cnt;
		philo[cnt].l_fork = &info->fork[cnt];
		if (cnt == info->menbers)
			philo[cnt].r_fork = &info->fork[0];
		else
			philo[cnt].r_fork = &info->fork[(cnt + 1)];
		cnt++;
	}
}

void	monitoring(t_philo *philo)
{
	
}



void	philo_move(t_philo *philo)
{
	while (1)
	{
		have_fork(philo);
		if (philo->now == EAT)
			do_sleep(philo);
	}
}

void	pthiread_start(t_info *info, t_philo *philo)
{
	int	cnt;

	cnt = 0;
	pthread_create(&info->thread, NULL, &monitoring, info);
	while (cnt < info->menbers)
	{
		pthread_create(&philo[cnt].thread, NULL, &philo_move, &philo[cnt]);
		cnt++;
	}
}

int	main(int argc, char **argv)
{
	t_info	*info;
	t_philo	*philo;

	if (argc != 5 && argc != 6)
		return (1);
	info = init_info(argc, argv);
	if (!info)
		return (1);
	init_philo(info, philo);
	make_pthread(info, philo);
}
