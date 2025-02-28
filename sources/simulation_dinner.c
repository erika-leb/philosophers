/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_dinner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:33:15 by ele-borg          #+#    #+#             */
/*   Updated: 2025/02/28 15:45:34 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_philo *p)
{
	safe_write(p, p->name, "has taken a fork");
}

void	t_think(t_table *table)
{
	long	time;

	if (table->nmb_of_philo % 2 == 0)
		return ;
	time = table->time_to_eat * 2 - table->time_to_sleep;
	if (time < 0)
		time = 0;
	precise_usleep(time);
}

void	t_eat(t_philo *p)
{
	struct timeval	time;

	pthread_mutex_lock(p->fst_fork);
	safe_write(p, p->name, "has taken a fork");
	pthread_mutex_lock(p->scd_fork);
	safe_write(p, p->name, "has taken a fork");
	gettimeofday(&time, NULL);
	long_set(&p->table->meal, &p->last_meal, get_time_in_ms(time));
	safe_write(p, p->name, "is eating");
	pthread_mutex_lock(&p->table->full_philos);
	(p->nb_meal)++;
	pthread_mutex_unlock(&p->table->full_philos);
	precise_usleep(p->table->time_to_eat);
	pthread_mutex_unlock(p->fst_fork);
	pthread_mutex_unlock(p->scd_fork);
}

void	*routine(void *philo)
{
	t_philo		*p;

	p = (t_philo *) philo;
	if (p->table->nmb_of_philo == 1)
	{
		one_philo(p);
		return (NULL);
	}
	while (bool_get(&p->table->begin, &p->table->start) == false)
		precise_usleep(1);
	if (p->name % 2 != 0)
		precise_usleep(30);
	while (bool_get(&p->table->simulation_status,
			&p->table->end_simulation) == false)
	{
		t_eat(p);
		safe_write(p, p->name, "is sleeping");
		precise_usleep(p->table->time_to_sleep);
		safe_write(p, p->name, "is thinking");
		t_think(p->table);
	}
	return (NULL);
}
