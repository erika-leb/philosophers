/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:06:49 by ele-borg          #+#    #+#             */
/*   Updated: 2025/02/26 11:27:05 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_all(t_table *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->nmb_of_philo)
	{
		pthread_mutex_destroy(&dinner->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&dinner->safe_write);
	pthread_mutex_destroy(&dinner->meal);
	pthread_mutex_destroy(&dinner->begin);
	free(dinner->forks);
	free(dinner->philos);
}

void exit_error(char *s, t_table *dinner)
{
	int i;

	i = 0;
	printf("%s\n", s);
	while (i < dinner->nmb_of_philo)
	{
		pthread_mutex_destroy(&dinner->forks[i]);
		i++;
	}
	free(dinner->forks);
	free(dinner->philos);
	pthread_mutex_destroy(&dinner->safe_write);
}

long	get_time_in_ms(struct timeval time)
{
	long	res;

	res = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (res);
}

void	precise_usleep(long usec)
{
	struct timeval	time;
	long			current;
	long			begin;
	long			rem;

	gettimeofday(&time, NULL);
	begin = time.tv_sec * 1000 + time.tv_usec / 1000;
	while (1)
	{
		gettimeofday(&time, NULL);
		current = time.tv_sec * 1000 + time.tv_usec / 1000;
		rem = usec - (current - begin);
		if (rem > 20)
			usleep(rem / 2);
		// if (current - begin < usec)
		// 	usleep(10);
		else
			break ;
	}
}
