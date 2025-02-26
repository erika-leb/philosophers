/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_dinner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:33:15 by ele-borg          #+#    #+#             */
/*   Updated: 2025/02/26 15:05:55 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_write(t_philo *philo, int id, char *s)
{
	struct timeval	time;
	long			current;
	static bool		flag = true;

	if (flag == false)
		return ;
	pthread_mutex_lock(&philo->table->safe_write);
	gettimeofday(&time, NULL);
	current = get_time_in_ms(time);
	// printf("%ld ", current - philo->table->start_time);
	printf("%ld ", current - long_get(&philo->table->time, &philo->table->start_time));
	printf("%d ", id);
	printf("%s\n", s);
	if (strcmp(s, "has died") == 0)
		flag = false;
	pthread_mutex_unlock(&philo->table->safe_write);
}

void	*routine(void *philo)
{
	t_philo		*p;
	struct		timeval	time;

	p = (t_philo *) philo;
	while (bool_get(&p->table->begin, &p->table->start) == false)
		// usleep(30);
	{
			precise_usleep(25);
	}
	if (p->name % 2 == 0)
		precise_usleep(30);
	while (1)
	{
		// perror("coco bango");
		// printf("time 3 = %ld\n", p->table->start_time);
		// printf("table->end_simulation 5 = %d\n", p-> table->end_simulation);
		if (bool_get(&p->table->simulation_status, &p->table->end_simulation) == true)
			break ;
		// perror("hola");
		pthread_mutex_lock(p->fst_fork);
		safe_write(p, p->name, "has taken a fork");
		if (bool_get(&p->table->simulation_status, &p->table->end_simulation) == true)
		{
			//perror("tumba");
			pthread_mutex_unlock(p->fst_fork);
			break ;
		}
		pthread_mutex_lock(p->scd_fork);
		safe_write(p, p->name, "has taken a fork");
		if (bool_get(&p->table->simulation_status, &p->table->end_simulation) == true)
		{
			//perror("la casa");
			pthread_mutex_unlock(p->fst_fork);
			pthread_mutex_unlock(p->scd_fork);
			break ;
		}
		gettimeofday(&time, NULL);
		long_set(&p->table->meal, &p->last_meal, get_time_in_ms(time));
		//p->last_meal = time.tv_sec * 1000 + time.tv_usec / 1000; //ou est ce que je le mets precisement ?
		safe_write(p, p->name, "is eating");
		pthread_mutex_lock(&p->table->full_philos);
		(p->nb_meal)++;
		pthread_mutex_unlock(&p->table->full_philos);
		precise_usleep(p->table->time_to_eat);
		pthread_mutex_unlock(p->fst_fork);
		pthread_mutex_unlock(p->scd_fork);
		if (bool_get(&p->table->simulation_status, &p->table->end_simulation) == true)
			break ;
		safe_write(p, p->name, "is sleeping");
		precise_usleep(p->table->time_to_sleep);
		if (bool_get(&p->table->simulation_status, &p->table->end_simulation) == true)
			break ;
		safe_write(p, p->name, "is thinking");
	}
	// perror("perra");
	return (NULL);
}

void	*control(void *dinner)
{
	t_table	*table;
	int		i;
	struct	timeval	time;
	int		all_full;

	table = (t_table *) dinner;
	// i = -1;
	// gettimeofday(&time, NULL);
	// long_set(&table->time, &table->start_time, get_time_in_ms(time));
	// while (++i < table->nmb_of_philo)
	// {
	// 	long_set(&table->meal, &table->philos[i].last_meal, get_time_in_ms(time));
	// 	// printf("last -meal philo %d = %ld\n", i, table->philos[i].last_meal);
	// }
	// bool_set(&table->begin, &table->start, true);
	// perror("partez");
	// printf("time 5 = %ld\n", table->start_time);
	i = 0;
	all_full = 0;
	while (table->end_simulation == false)
	{
		gettimeofday(&time, NULL);
		if (get_time_in_ms(time) - long_get(&table->meal, &table->philos[i].last_meal) > table->time_to_die)
		{
			bool_set(&table->simulation_status, &table->end_simulation, true);
			safe_write(&table->philos[i], table->philos[i].name, "has died");
		}
		if (long_get(&table->full_philos, &table->philos[i].nb_meal) >= table->max_nmb_of_meals)
			all_full++;
		if (i == table->nmb_of_philo - 1)
		{
			if (all_full == table->nmb_of_philo - 1)
				bool_set(&table->simulation_status, &table->end_simulation, true);
			else
			{
				all_full = 0;
				i = 0;
			}
		}
		else
			i++;
	}
	// printf("time 1 = %ld\n", table->start_time);
	return (NULL);
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

	// gettimeofday(&start, NULL);
	// // dinner->start_time = get_time_in_ms(start);
	// long_set(&dinner->time, &dinner->start_time, get_time_in_ms(start));
	// while (++i < dinner->nmb_of_philo)
	// 	long_set(&dinner->meal, &dinner->philos[i].last_meal, get_time_in_ms(start));
	// // dinner->start_time = get_time_in_ms(start);
	// bool_set(&dinner->begin, &dinner->start, true);

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
