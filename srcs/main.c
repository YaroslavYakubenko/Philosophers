/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 22:22:26 by yaroslav          #+#    #+#             */
/*   Updated: 2024/10/14 23:14:15 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_simulation	sim;
	pthread_t		*threads;
	int				i;
	int				all_alive;

	if (!validate_arguments(ac, av))
		return (1);
	if (!init_simulation(&sim, ac, av))
		return (1);
	threads = malloc(sizeof(pthread_t) * sim.numbers_of_philosophers);
	if (!threads)
		return (1);
	i = 0;
	while (i < sim.numbers_of_philosophers)
	{
		pthread_create(&threads[i], NULL, philo_routine,
			(void *)&sim.philos[i]);
		i++;
	}
	while (1)
	{
		all_alive = 1;
		i = 0;
		while (i < sim.numbers_of_philosophers)
		{
			if (sim.is_alive[i] == 0)
			{
				all_alive = 0;
				break ;
			}
			i++;
		}
		if (!all_alive)
			break ;
	}
	i = 0;
	while (i < sim.numbers_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	free(sim.philos);
	free(sim.forks);
	free(sim.is_alive);
	return (0);
}
