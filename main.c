/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:52:09 by stakimot          #+#    #+#             */
/*   Updated: 2023/05/04 16:01:10 by stakimot         ###   ########.fr       */
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

bool	move_check(t_philo *philo)
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
		if (move_check(philo))
			break ;
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

bool	check_die(t_info *info)
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
			pthread_mutex_unlock(&info->check_die);
			return (true);
		}
		pthread_mutex_unlock(&info->check_die);
	}
	return (false);
}

bool	check_full(t_info *info)
{
	int	full_menbers;

	if (info->must_eat == 0)
		return (false);
	pthread_mutex_lock(&info->check_full);
	full_menbers = info->full_menbers;
	pthread_mutex_unlock(&info->check_full);
	if (full_menbers == info->menbers)
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
	while (1)
	{
		if (check_die(info))
			break ;
		if (check_full(info))
			break ;
		my_usleep(10);
	}
}

void	pthread_start(t_info *info, t_philo *philo)
{
	int	cnt;

	cnt = 0;
	info->start = get_now_time();
	while (cnt < info->menbers)
	{
		pthread_create(&philo[cnt].thread, NULL, &philo_move, &philo[cnt]);
		cnt++;
	}
	cnt = 0;
	monitoring(info);
	while (cnt < info->menbers)
		pthread_join(philo[cnt++].thread, NULL);
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
	info->philo = philo;
	pthread_start(info, philo);
}
