/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:59:55 by ele-borg          #+#    #+#             */
/*   Updated: 2025/02/28 15:44:41 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_simulation(t_table *table)
{
	struct timeval	time;
	int				i;

	gettimeofday(&time, NULL);
	long_set(&table->time, &table->start_time, get_time_in_ms(time));
	i = -1;
	while (++i < table->nmb_of_philo)
		long_set(&table->meal, &table->philos[i].last_meal,
			get_time_in_ms(time));
	bool_set(&table->begin, &table->start, true);
}

static void	handle_i(int *i, t_table *table, int *all_full)
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
	usleep(100);
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
	precise_usleep(60);
	while (table->end_simulation == false)
	{
		gettimeofday(&time, NULL);
		if (get_time_in_ms(time) - long_get(&table->meal,
				&table->philos[i].last_meal) > table->time_to_die)
		{
			bool_set(&table->simulation_status, &table->end_simulation, true);
			safe_write(&table->philos[i], table->philos[i].name, "has died");
		}
		if (table->max_nmb_of_meals != -1 && (long_get(&table->full_philos,
					&table->philos[i].nb_meal) >= table->max_nmb_of_meals))
			all_full++;
		handle_i(&i, table, &all_full);
	}
	return (NULL);
}
