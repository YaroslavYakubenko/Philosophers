/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 22:22:26 by yaroslav          #+#    #+#             */
/*   Updated: 2024/10/31 17:32:52 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_simulation *sim)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&sim->print_mutex);
	while (i < sim->numbers_of_philosophers)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	free(sim->philos);
	free(sim->forks);
}

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
	i = -1;
	while (++i < sim.numbers_of_philosophers)
		pthread_create(&threads[i], NULL, philo_routine,
			(void *)&sim.philos[i]);
	i = -1;
	while (++i < sim.numbers_of_philosophers)
		pthread_join(threads[i], NULL);
	free_all(&sim);
	free(threads);
	return (0);
}
