/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_dinner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:33:15 by ele-borg          #+#    #+#             */
/*   Updated: 2025/02/20 18:06:19 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_write(t_philo *philo, int id, char *s)
{
	struct timeval	time;
	long			current;

	pthread_mutex_lock(&philo->table->safe_write);
	gettimeofday(&time, NULL);
	current = get_time_in_ms(time);
	//printf("%ld \n", current);
	printf("%ld ", current - philo->table->start_time);
	printf("%d ", id);
	printf("%s\n", s);
	pthread_mutex_unlock(&philo->table->safe_write);
}

void	*routine(void *philo)
{
	t_philo *p;

	p = (t_philo *) philo;

	// if (p->name % 2 == 0)
	// 	safe_write(p, p->name, "is eating");
	// else
	// 	safe_write(p, p->name, "is sleeping");
	return (NULL);
}

int	init_dinner(t_table *dinner)
{
	int	i;

	i = 0;
	if (init_mutex(dinner) == -1)
	{
		free(dinner->forks);
		free(dinner->philos);
		return (-1);
	}
	// initialiser les mutex et les fermer dans exit
	while (i < dinner->nmb_of_philo)
	{
		if (pthread_create(&dinner->philos[i].id, NULL, routine, (void *)&dinner->philos[i]))
			return (exit_error("philo: error pthread creation", dinner), -1);
		i++;
	}
	i = 0;
	while(i < dinner->nmb_of_philo)
	{
		if (pthread_join(dinner->philos[i].id, NULL))
			return (exit_error("philo: error pthread join", dinner), -1);
		i++;
	}
	return (0);
}
