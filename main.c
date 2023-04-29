/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:52:09 by stakimot          #+#    #+#             */
/*   Updated: 2023/04/29 22:25:45 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_now_time()
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
	{
		usleep(1);
	}
}

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
	info->start = get_now_time();
	if (argc == 6)
		info->must_eat = ft_atoi(argv[5]);
	else
		info->must_eat = -1;
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
		if (cnt == info->menbers - 1)
			philo[cnt].r_fork = &info->fork[0];
		else
			philo[cnt].r_fork = &info->fork[(cnt + 1)];
		cnt++;
	}
	return (philo);
}

// void	monitoring(t_philo *philo)
// {
// }

void	have_fork(t_philo *philo)
{
	if (philo->philo_number % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		printf("%d l_fork\n", philo->philo_number);
		pthread_mutex_lock(philo->r_fork);
		printf("%d r_fork\n", philo->philo_number);
	}
	else
	{
		my_usleep(10);
		pthread_mutex_lock(philo->r_fork);
		printf("%d r_fork\n", philo->philo_number);
		pthread_mutex_lock(philo->l_fork);
		printf("%d l_fork\n", philo->philo_number);
	}
}

void	happy_eat(t_philo *philo)
{
	printf("%d eat\n", philo->philo_number);
	my_usleep(philo->info->eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	printf("%d unlock\n", philo->philo_number);
}

void	happy_sleep(t_philo *philo)
{
	my_usleep(philo->info->sleep);
	printf("%d sleep\n", philo->philo_number);
}

void	happy_think(t_philo *philo)
{
	printf("%d think\n", philo->philo_number);
}

void	*philo_move(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
	{
		have_fork(philo);
		happy_eat(philo);
		happy_sleep(philo);
		happy_think(philo);
	}
	return (NULL);
}

void	pthread_start(t_info *info, t_philo *philo)
{
	int	cnt;

	cnt = 0;
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
	philo = init_philo(info);
	pthread_start(info, philo);
}
