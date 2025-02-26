/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:41:37 by ele-borg          #+#    #+#             */
/*   Updated: 2025/02/26 20:03:33 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

# define mutex_t pthread_mutex_t

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				name;
	pthread_t		id;
	mutex_t			*fst_fork;
	mutex_t			*scd_fork;
	t_table			*table;
	bool			dead;
	long			last_meal;
	long			nb_meal;
	bool			full;
}					t_philo;

typedef struct s_table
{
	long			nmb_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_nmb_of_meals; // -1 si rien
	long			start_time;
	mutex_t			*forks;
	t_philo			*philos;
	mutex_t			safe_write;
	pthread_t		monitor;
	bool			end_simulation;
	bool			start;
	bool			flag_write;
	mutex_t			flag;
	mutex_t			begin;  //faut il commencer la simulation ?
	mutex_t			simulation_status; // faut il terminer le diner ou non ?
	mutex_t			meal; //enregistrement du dernier repas
	mutex_t			time; //toucher a start_time
	mutex_t			full_philos;
}					t_table;

//init
int			init_forks(t_table *dinner);
int			init_table(t_table *dinner);
int			init_mutex(t_table *dinner);
int			init_dinner(t_table *dinner);

//main
void		*routine(void *philo);

//parsing
long		ft_atol(char *s);
int			parsing(char **av, t_table *dinner);
t_table		init_arg(char **av);

//simulation_dinner
void		*control(void *dinner);
void		*routine(void *philo);

//synchronisation
void		bool_set(mutex_t *mutex, bool *to_set, bool value);
bool		bool_get(mutex_t *mutex, bool *to_get);
void		long_set(mutex_t *mutex, long *to_set, long value);
long		long_get(mutex_t *mutex, long *to_get);
void		safe_write(t_philo *philo, int id, char *s);

//utils
void		exit_error(char *s, t_table *dinner);
void		free_all(t_table *dinner);
long		get_time_in_ms(struct timeval time);
void		precise_usleep(long usec);

#endif
