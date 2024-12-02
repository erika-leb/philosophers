/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:44:17 by ele-borg          #+#    #+#             */
/*   Updated: 2024/11/16 22:15:13 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread(void *philo)
{
	t_philo *p;
	
	p = (t_philo *) philo;
	printf("philosopher %d active id = %lu\n", p->name, p->id);
	return (NULL);
}

void exit_error(char *s, t_table *dinner)
{
	printf("%s\n", s);
	free(dinner->forks);
	free(dinner->philos);
}

int	init_forks(t_table *dinner)
{
	int	i;

	i = 0;
	dinner->forks = malloc(sizeof(int) * (dinner->nmb_of_philo)); // doute
	if (dinner->forks == NULL)
	{
		printf("error malloc\n");
		return (-1);
	}
	while (i < dinner->nmb_of_philo)
	{
		dinner->forks[i] = 0;
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
		printf("error malloc\n");
		free(dinner->forks);
		return (-1);
	}
		while (i < dinner->nmb_of_philo)
	{
		dinner->philos[i].name = i + 1;
		dinner->philos[i].l_fork = &dinner->forks[i];
		if (i != 0)
		{
			dinner->philos[i].r_fork = &dinner->forks[i - 1];
			//printf("philopher %d : fork left = %d fork right = %d\n", i, i, i - 1);
		}
		else
		{
			dinner->philos[i].r_fork = &dinner->forks[dinner->nmb_of_philo - 1];
			//printf("philopher %d : fork left = %d fork right = %d\n", i, i, dinner->nmb_of_philo - 1);
		}
		i++;
	}
	return (0);
}

int	init_dinner(t_table *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->nmb_of_philo)
	{
		if (pthread_create(&dinner->philos[i].id, NULL, thread, (void *)&dinner->philos[i]))
			return (exit_error("error pthread creation", dinner), -1);
		i++;
	}
	i = 0;
	while(i < dinner->nmb_of_philo)
	{
		if (pthread_join(dinner->philos[i].id, NULL))
			return (exit_error("error pthread join", dinner), -1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_table	dinner;
	
	if (ac != 5 && ac != 6)
	{
		printf("wrong number of arguments\n");
		return (0);
	}
	dinner = init_arg(av);
	if (parsing(av, &dinner) == -1)
		return (0);
	if (init_forks(&dinner) == -1)
		return (-1);
	if (init_table(&dinner) == -1)
		return (-1);
	if (init_dinner(&dinner) == -1)
		return (-1);
	return (0);
}
