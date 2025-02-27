/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_dinner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:33:15 by ele-borg          #+#    #+#             */
/*   Updated: 2025/02/27 20:43:51 by ele-borg         ###   ########.fr       */
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
	else
	{
		time = table->time_to_eat * 2 - table->time_to_sleep;
		if (time < 0)
			time = 0;
		precise_usleep(time);
	}
}

void	*routine(void *philo)
{
	t_philo		*p;
	struct		timeval	time;

	p = (t_philo *) philo;
	if (p->table->nmb_of_philo == 1)
	{
		one_philo(p);
		return (NULL);
	}
	while (bool_get(&p->table->begin, &p->table->start) == false)
		// perror("hola");
		precise_usleep(1);
	if (p->name % 2 != 0)
		precise_usleep(30);
	while (bool_get(&p->table->simulation_status, &p->table->end_simulation) == false)
	{
		// perror("que pasaria");
		pthread_mutex_lock(p->fst_fork);
		safe_write(p, p->name, "has taken a fork");
		pthread_mutex_lock(p->scd_fork);
		safe_write(p, p->name, "has taken a fork");
		gettimeofday(&time, NULL);
		long_set(&p->table->meal, &p->last_meal, get_time_in_ms(time));
		safe_write(p, p->name, "is eating");
		pthread_mutex_lock(&p->table->full_philos);
		(p->nb_meal)++;
		// printf("philo %d a mange %ld fois\n", p->name, p->nb_meal);
		pthread_mutex_unlock(&p->table->full_philos);
		precise_usleep(p->table->time_to_eat);
		pthread_mutex_unlock(p->fst_fork);
		pthread_mutex_unlock(p->scd_fork);
		safe_write(p, p->name, "is sleeping");
		precise_usleep(p->table->time_to_sleep);
		safe_write(p, p->name, "is thinking");
		t_think(p->table);
		// perror("solos");
	}
	// perror("si estuvieramos");
	return (NULL);
}

void	start_simulation(t_table *table)
{
	struct	timeval	time;
	int		i;

	gettimeofday(&time, NULL);
	long_set(&table->time, &table->start_time, get_time_in_ms(time));
	i = -1;
	while (++i < table->nmb_of_philo)
		long_set(&table->meal, &table->philos[i].last_meal,
			get_time_in_ms(time));
	// printf("time start = %ld\n", get_time_in_ms(time));
	bool_set(&table->begin, &table->start, true);
	// gettimeofday(&time, NULL);
	// printf("time ou le start est lance = %ld\n", get_time_in_ms(time));
}

void	handle_i(int *i, t_table *table, int *all_full)
{
	if ((*i) == table->nmb_of_philo - 1)
	{
		if (*(all_full) == table->nmb_of_philo)
			bool_set(&table->simulation_status, &table->end_simulation, true);
		else
		{
			(*all_full) = 0;
			(*i) = 0;
		}
	}
	else
		(*i)++;
}

void	*control(void *dinner)
{
	t_table			*table;
	int				i;
	struct timeval	time;
	int				all_full;

	table = (t_table *) dinner;
	start_simulation(table);
	i = 0;
	all_full = 0;
	precise_usleep(1);
	while (table->end_simulation == false)
	{
		gettimeofday(&time, NULL);
		if (get_time_in_ms(time) - long_get(&table->meal,
				&table->philos[i].last_meal) > table->time_to_die)
		{
			// perror("es salvaje");
			bool_set(&table->simulation_status, &table->end_simulation, true);
			safe_write(&table->philos[i], table->philos[i].name, "has died");
		}
		if (table->max_nmb_of_meals!= -1 && (long_get(&table->full_philos,
			&table->philos[i].nb_meal) >= table->max_nmb_of_meals))
		{
			all_full++;
			// printf("all_full = %d, philo[%d] a mange %ld fois\n", all_full, table->philos[i].name, table->philos[i].nb_meal);
		}
		handle_i(&i, table, &all_full);
		//perror("telo doy");
	}
	//perror("pra voce");
	return (NULL);
}
