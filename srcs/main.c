/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 22:22:26 by yaroslav          #+#    #+#             */
/*   Updated: 2024/10/21 19:12:41 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_simulation	sim;
	pthread_t		*threads;
	int				i;

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
	check_philo_status(&sim);
	check_philo_meals(&sim);
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
