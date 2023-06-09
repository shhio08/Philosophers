/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:52:09 by stakimot          #+#    #+#             */
/*   Updated: 2023/06/09 10:17:34 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	// pthread_mutex_destroy(info->fork);
	pthread_mutex_destroy(&info->check_die);
	pthread_mutex_destroy(&info->check_full);
	// while (cnt < info->menbers)
	// {
	// 	pthread_mutex_destroy(philo->l_fork);
	// 	pthread_mutex_destroy(philo->r_fork);
	// }
	cnt = 0;
	while (cnt < info->menbers)
		pthread_mutex_destroy(&info->fork[cnt++]);
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
	free(info->fork);
	free(info);
	free(philo);
}

// 	__attribute__((destructor)) static void destructor()
// {
//     system("leaks -q philo");
// }