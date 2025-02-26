/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:44:17 by ele-borg          #+#    #+#             */
/*   Updated: 2025/02/26 16:12:30 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	dinner;

	if (ac != 5 && ac != 6)
	{
		printf("philo: wrong number of arguments\n");
		return (0);
	}
	dinner = init_arg(av);
	if (parsing(av, &dinner) == -1)
		return (0);
	//printf("end_simulation = %d\n", dinner.end_simulation);
	if (init_forks(&dinner) == -1)
		return (-1);
	//printf("end_simulation 2 = %d\n", dinner.end_simulation);
	if (init_table(&dinner) == -1)
		return (-1);
	if (init_dinner(&dinner) == -1)
		return (-1);
	// perror("pero en mi");
	free_all(&dinner);
	// perror("la que no quiere");
	return (0);
}
