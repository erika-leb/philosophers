/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:11:22 by ele-borg          #+#    #+#             */
/*   Updated: 2025/02/25 18:36:26 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_table *dinner)
{
	int	i;

	i = 0;
	dinner->forks = malloc(sizeof(mutex_t) * (dinner->nmb_of_philo)); // doute
	if (dinner->forks == NULL)
	{
		printf("philo: error malloc\n");
		return (-1);
	}
	while (i < dinner->nmb_of_philo)
	{
		//perror("hola");
		if (pthread_mutex_init(&dinner->forks[i], NULL) != 0)
		{
			write(2, "philo: Erreur pthread_mutex_init\n", 34);
			return (-1);
		}
		//dinner->forks[i] = i + 1; // mettre les mutex ici ?
		i++;
	}
	// i = 0;
	// while (i < dinner->nmb_of_philo)
	// {
	// 	printf("fork %d = %d\n", i, dinner->forks[i]);
	// 	i++;
	// }
	return (0);
}

int	init_table(t_table *dinner)
{
	int	i;

	i = 0;
	dinner->philos = malloc(sizeof(t_philo) * (dinner->nmb_of_philo)); //doute
	if (dinner->philos == NULL)
	{
		printf("philo: error malloc\n");
		free(dinner->forks);
		return (-1);
	}
	while (i < dinner->nmb_of_philo)
	{
		dinner->philos[i].name = i + 1;
		if (i % 2 == 0) //philo impair om commence par la droite
		{
			if (i != 0) // condition a rajouter
			{
				dinner->philos[i].fst_fork = &dinner->forks[i - 1];
				dinner->philos[i].scd_fork = &dinner->forks[i];
				// printf("philo %d  pris en premier la fourchette %d et en second la %d\n", i + 1, i - 1, i);
			}
			else
			{
				dinner->philos[i].fst_fork = &dinner->forks[dinner->nmb_of_philo - 1];
				dinner->philos[i].scd_fork = &dinner->forks[i];
				// printf("philo %d  pris en premier la fourchette %ld et en second la %d\n", i + 1, dinner->nmb_of_philo - 1, i);
			}
		}
		else //philo pair on commence par la gauche
		{
			// if (i != dinner->nmb_of_philo - 1)
			// {
				dinner->philos[i].fst_fork = &dinner->forks[i];
				dinner->philos[i].scd_fork = &dinner->forks[i - 1];
				// printf("philo %d  pris en premier la fourchette %d et en second la %d\n", i + 1, i, i - 1);
			// }
			// else
			// {
			// 	dinner->philos[i].fst_fork = &dinner->forks[i];
			// 	dinner->philos[i].scd_fork = &dinner->forks[i - 1];
			// }
		}
		dinner->philos[i].table = dinner;
		dinner->philos[i].dead = false;
		dinner->philos[i].last_meal = dinner->start_time;
		// printf("st meal = %ld\n", dinner->philos[i].last_meal);
		i++;
	}
	return (0);
}

int	init_mutex(t_table *dinner)
{
	if (pthread_mutex_init(&dinner->safe_write, NULL) != 0)
	{
		write(2, "philo: Erreur pthread_mutex_init\n", 34);
		return (-1);
	}
	if (pthread_mutex_init(&dinner->simulation_status, NULL) != 0)
	{
		write(2, "philo: Erreur pthread_mutex_init\n", 34);
		return (-1);
	}
	if (pthread_mutex_init(&dinner->meal, NULL) != 0)
	{
		write(2, "philo: Erreur pthread_mutex_init\n", 34);
		return (-1);
	}
	if (pthread_mutex_init(&dinner->begin, NULL) != 0)
	{
		write(2, "philo: Erreur pthread_mutex_init\n", 34);
		return (-1);
	}
	if (pthread_mutex_init(&dinner->time, NULL) != 0)
	{
		write(2, "philo: Erreur pthread_mutex_init\n", 34);
		return (-1);
	}
	return (0);
}


