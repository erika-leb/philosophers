/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:41:37 by ele-borg          #+#    #+#             */
/*   Updated: 2024/11/16 22:19:44 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>

typedef struct s_philo
{
	int			name;
	pthread_t	id;
	int			*r_fork;
	int			*l_fork;
}	t_philo;

typedef struct s_table
{
	int				nmb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_nmb_of_meals;
	struct timeval	start_time;
	int				*forks;
	t_philo			*philos;
}	t_table;

int		ft_atoi(char *s);
int		parsing(char **av, t_table *dinner);
t_table	init_arg(char **av);

# endif