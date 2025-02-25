/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:15:37 by ele-borg          #+#    #+#             */
/*   Updated: 2025/02/25 12:51:55 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	bool_set(mutex_t *mutex, bool *to_set, bool value)
{
	pthread_mutex_lock(mutex);
	*to_set = value;
	pthread_mutex_unlock(mutex);
}

bool	bool_get(mutex_t *mutex, bool *to_get)
{
	bool	res;

	pthread_mutex_lock(mutex);
	res = *to_get;
	pthread_mutex_unlock(mutex);
	return (res);
}

void	long_set(mutex_t *mutex, long *to_set, long value)
{
	pthread_mutex_lock(mutex);
	*to_set = value;
	pthread_mutex_unlock(mutex);
}

long	long_get(mutex_t *mutex, long *to_get)
{
	long	res;

	pthread_mutex_lock(mutex);
	res = *to_get;
	pthread_mutex_unlock(mutex);
	return (res);
}
