/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:35:06 by stakimot          #+#    #+#             */
/*   Updated: 2023/05/16 16:39:20 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <stdbool.h>

typedef enum e_now
{
	TAKEN_FORK,
	EAT,
	SLEEP,
	THINK,
}	t_now;

typedef struct s_info
{
	int				menbers;
	int				die;
	int				eat;
	int				sleep;
	int				must_eat;
	long			start;
	bool			check;
	bool			full;
	int				full_menbers;
	struct s_philo	*philo;
	pthread_t		thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	check_die;
	pthread_mutex_t	check_full;
}	t_info;

typedef struct s_philo
{
	t_info			*info;
	int				philo_number;
	long			last_eat;
	int				eat_cnt;
	// t_now			now;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

int		ft_atoi(const char *str);
t_info	*init_info(int argc, char **argv);
t_philo	*init_philo(t_info *info);
void	monitoring(t_info *info);
void	have_fork(t_philo *philo);
void	happy_eat(t_philo *philo);
void	happy_think(t_philo *philo);
void	happy_sleep(t_philo *philo);
void	*philo_move(void *p);
long	get_now_time(void);
void	my_usleep(int num);
void	print_move(t_philo *philo, t_now move);

#endif
