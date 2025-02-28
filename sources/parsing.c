/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:19:55 by ele-borg          #+#    #+#             */
/*   Updated: 2025/02/28 15:46:40 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *s)
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
		printf("philo: no negative arguments\n");
		return (-1);
	}
	while (*s >= '0' && *s <= '9' && i++ <= 13)
	{
		r = r * 10 + (*s - '0');
		s++;
	}
	if (i > 10 || r > INT_MAX)
	{
		printf("philo: int too long\n");
		return (-1);
	}
	return (r);
}

int	parsing(char **av, t_table *dinner)
{
	dinner->nmb_of_philo = ft_atol(av[1]);
	if (dinner->nmb_of_philo == -1 || dinner->nmb_of_philo == 0)
		return (-1);
	dinner->time_to_die = ft_atol(av[2]);
	if (dinner->time_to_die == -1)
		return (-1);
	dinner->time_to_eat = ft_atol(av[3]);
	if (dinner->time_to_eat == -1)
		return (-1);
	dinner->time_to_sleep = ft_atol(av[4]);
	if (dinner->time_to_sleep == -1)
		return (-1);
	if (av[5])
	{
		dinner->max_nmb_of_meals = ft_atol(av[5]);
		if (dinner->max_nmb_of_meals == -1)
			return (-1);
	}
	return (0);
}

t_table	init_arg(char **av)
{
	struct timeval	start;
	t_table			dinner;

	gettimeofday(&start, NULL);
	dinner.nmb_of_philo = 0;
	dinner.time_to_die = 0;
	dinner.time_to_eat = 0;
	dinner.time_to_sleep = 0;
	dinner.start_time = get_time_in_ms(start);
	if (av[5])
		dinner.max_nmb_of_meals = 0;
	else
		dinner.max_nmb_of_meals = -1;
	dinner.forks = NULL;
	dinner.philos = NULL;
	dinner.end_simulation = false;
	dinner.start = false;
	dinner.flag_write = true;
	return (dinner);
}
