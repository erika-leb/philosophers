/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:19:55 by ele-borg          #+#    #+#             */
/*   Updated: 2024/11/16 22:23:53 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *s)
{
	long	r;
	int		i;

	r = 0;
	i = 0;
	while ((*s >= 9 && s[i] <= 13) || *s == ' ')
		s++;
	while (*s == '+')
		s++;
	if (*s == '-')
	{
		printf("no negative arguments\n");
		return (-1);
	}
	while (*s >= '0' && *s <= '9' && i++ <= 13)
	{
		r = r * 10 + (*s - '0');
		s++;
	}
	if (i > 10 || r > INT_MAX)
	{
		printf("int too long\n");
		return (-1);
	}
	return ((int) r);
}
int	parsing(char **av, t_table *dinner)
{
	dinner->nmb_of_philo = ft_atoi(av[1]);
	if (dinner->nmb_of_philo == -1 || dinner->nmb_of_philo == 0)
		return (-1);
	dinner->time_to_die = ft_atoi(av[2]);
	if (dinner->time_to_die == -1)
		return (-1);
	dinner->time_to_eat = ft_atoi(av[3]);
	if (dinner->time_to_eat == -1)
		return (-1);
	dinner->time_to_sleep = ft_atoi(av[4]);
	if (dinner->time_to_sleep == -1)
		return (-1);
	if (av[5])
	{
		dinner->max_nmb_of_meals = ft_atoi(av[5]);
		if (dinner->max_nmb_of_meals == -1)
			return (-1);
	}
	return (0);
}

t_table	init_arg(char **av)
{
	struct timeval start;

	gettimeofday(&start, NULL);
	t_table	dinner;
	dinner.nmb_of_philo = 0;
	dinner.time_to_die = 0;
	dinner.time_to_eat = 0;
	dinner.time_to_sleep = 0;
	dinner.start_time = start;
	if (av[5])
		dinner.max_nmb_of_meals = 0;
	else 
		dinner.max_nmb_of_meals = -1; // attention a bien gerer ce cas
	dinner.forks = NULL;
	dinner.philos = NULL;
	return (dinner);
}
