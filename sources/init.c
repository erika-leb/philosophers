/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:11:22 by ele-borg          #+#    #+#             */
/*   Updated: 2025/02/26 16:37:11 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_table *dinner)
{
	int	i;

	i = 0;
	dinner->forks = malloc(sizeof(mutex_t) * (dinner->nmb_of_philo));
	if (dinner->forks == NULL)
	{
		printf("philo: error malloc\n");
		return (-1);
	}
	while (i < dinner->nmb_of_philo)
	{
		if (pthread_mutex_init(&dinner->forks[i], NULL) != 0)
		{
			write(2, "philo: Erreur pthread_mutex_init\n", 34);
			return (-1);
		}
		//dinner->forks[i] = i + 1; // mettre les mutex ici ?
		i++;
	}
	return (0);
}

void	init_philo(t_philo *philo, t_table *table, int i)
{
	if (i % 2 == 0) //philo impair om commence par la droite
	{
		if (i != 0)
			table->philos[i].fst_fork = &table->forks[i - 1];
		else
			table->philos[i].fst_fork = &table->forks[table->nmb_of_philo - 1];
		table->philos[i].scd_fork = &table->forks[i];
	}
	else //philo pair on commence par la gauche
	{
			table->philos[i].fst_fork = &table->forks[i];
			table->philos[i].scd_fork = &table->forks[i - 1];
	}
	philo->table = table;
	philo->dead = false;
	philo->last_meal = table->start_time;
	philo->nb_meal = 0;
	philo->full = false;
}

int	init_table(t_table *dinner)
{
	int	i;

	i = 0;
	dinner->philos = malloc(sizeof(t_philo) * (dinner->nmb_of_philo));
	if (dinner->philos == NULL)
		return (printf("philo: error malloc\n"), free(dinner->forks), -1);
	while (i < dinner->nmb_of_philo)
	{
		dinner->philos[i].name = i + 1;
		init_philo(&dinner->philos[i], dinner, i);
		i++;
	}
	return (0);
}

int	init_mutex(t_table *dinner)
{
	if (pthread_mutex_init(&dinner->safe_write, NULL) != 0)
		return (write(2, "philo: Erreur pthread_mutex_init\n", 34), -1);
	if (pthread_mutex_init(&dinner->simulation_status, NULL) != 0)
		return (write(2, "philo: Erreur pthread_mutex_init\n", 34), -1);
	if (pthread_mutex_init(&dinner->meal, NULL) != 0)
		return (write(2, "philo: Erreur pthread_mutex_init\n", 34), -1);
	if (pthread_mutex_init(&dinner->begin, NULL) != 0)
		return (write(2, "philo: Erreur pthread_mutex_init\n", 34), -1);
	if (pthread_mutex_init(&dinner->time, NULL) != 0)
		return (write(2, "philo: Erreur pthread_mutex_init\n", 34), -1);
	if (pthread_mutex_init(&dinner->full_philos, NULL) != 0)
		return (write(2, "philo: Erreur pthread_mutex_init\n", 34), -1);
	if (pthread_mutex_init(&dinner->flag, NULL) != 0)
		return (write(2, "philo: Erreur pthread_mutex_init\n", 34), -1);
	return (0);
}

int	init_dinner(t_table *dinner)
{
	int	i;
	struct timeval start;

	i = 0;
	if (init_mutex(dinner) == -1)
		return (free(dinner->forks), free(dinner->philos), -1);
	while (i < dinner->nmb_of_philo)
	{
		if (pthread_create(&dinner->philos[i].id, NULL, routine, (void *)&dinner->philos[i]))
			return (exit_error("philo: error pthread creation", dinner), -1);
		i++;
	}
	if (pthread_create(&dinner->monitor, NULL, control, (void *)dinner))
		return (exit_error("philo: error pthread creation", dinner), -1);
	i = -1;
	gettimeofday(&start, NULL);
	long_set(&dinner->time, &dinner->start_time, get_time_in_ms(start));
	while (++i < dinner->nmb_of_philo)
	{
		long_set(&dinner->meal, &dinner->philos[i].last_meal, get_time_in_ms(start));
		// printf("last -meal philo %d = %ld\n", i, dinner->philos[i].last_meal);
	}
	bool_set(&dinner->begin, &dinner->start, true);
	i = 0;
	while(i < dinner->nmb_of_philo)
	{
		if (pthread_join(dinner->philos[i].id, NULL))
			return (exit_error("philo: error pthread join", dinner), -1);
		i++;
	}
	if (pthread_join(dinner->monitor, NULL))
		return (exit_error("philo: error pthread join", dinner), -1);
	return (0);
}
