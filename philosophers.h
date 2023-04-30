/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:35:06 by stakimot          #+#    #+#             */
/*   Updated: 2023/04/30 19:09:27 by stakimot         ###   ########.fr       */
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
	struct s_philo	*philo;
	pthread_t		thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*mutex;
}	t_info;

typedef struct s_philo
{
	t_info			*info;
	int				philo_number;
	long			last_eat;
	int				eat_cnt;
	t_now			now;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

int	ft_atoi(const char *str);

#endif
