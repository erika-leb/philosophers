/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchronisation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:15:37 by ele-borg          #+#    #+#             */
/*   Updated: 2025/02/28 15:52:01 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	bool_set(pthread_mutex_t *mutex, bool *to_set, bool value)
{
	pthread_mutex_lock(mutex);
	*to_set = value;
	pthread_mutex_unlock(mutex);
}

bool	bool_get(pthread_mutex_t *mutex, bool *to_get)
{
	bool	res;

	pthread_mutex_lock(mutex);
	res = *to_get;
	pthread_mutex_unlock(mutex);
	return (res);
}

void	long_set(pthread_mutex_t *mutex, long *to_set, long value)
{
	pthread_mutex_lock(mutex);
	*to_set = value;
	pthread_mutex_unlock(mutex);
}

long	long_get(pthread_mutex_t *mutex, long *to_get)
{
	long	res;

	pthread_mutex_lock(mutex);
	res = *to_get;
	pthread_mutex_unlock(mutex);
	return (res);
}

void	safe_write(t_philo *philo, int id, char *s)
{
	struct timeval	time;
	long			current;

	pthread_mutex_lock(&philo->table->safe_write);
	if (bool_get(&philo->table->flag, &philo->table->flag_write) == false)
	{
		pthread_mutex_unlock(&philo->table->safe_write);
		return ;
	}
	gettimeofday(&time, NULL);
	current = get_time_in_ms(time);
	ft_putstr_fd(ft_ltoa(current - long_get(&philo->table->time,
				&philo->table->start_time)));
	ft_putstr_fd(" ");
	ft_putstr_fd(ft_ltoa((long) id));
	ft_putstr_fd(" ");
	ft_putstr_fd(s);
	ft_putstr_fd("\n");
	if (ft_strcmp(s, "has died") == 0)
		bool_set(&philo->table->flag, &philo->table->flag_write, false);
	pthread_mutex_unlock(&philo->table->safe_write);
}
