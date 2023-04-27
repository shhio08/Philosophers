/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:35:06 by stakimot          #+#    #+#             */
/*   Updated: 2023/04/27 15:57:48 by stakimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

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
	pthread_mutex_t	*fork;
	pthread_t		thread;
}	t_info;

typedef struct s_philo
{
	t_info			*info;
	int				philo_number;
	t_now			now;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

int	ft_atoi(const char *str);

#endif
