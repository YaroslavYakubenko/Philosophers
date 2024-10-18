/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaroslav <yaroslav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 22:22:26 by yaroslav          #+#    #+#             */
/*   Updated: 2024/10/18 15:56:34 by yaroslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*monitor_philos(void *arg)
// {
// 	t_simulation	*sim;
// 	int				i;
// 	int				all_alive;

// 	sim = (t_simulation *)arg;
// 	while (1)
// 	{
// 		all_alive = 1;
// 		i = 0;
// 		while (i < sim->numbers_of_philosophers)
// 		{
// 			if (sim->is_alive[i] == 0)
// 			{
// 				all_alive = 0;
// 				break ;
// 			}
// 			i++;
// 		}
// 		if (!all_alive)
// 			break ;
// 		usleep(1000);
// 	}
// 	return (NULL);
// }

int	main(int ac, char **av)
{
	t_simulation	sim;
	pthread_t		*threads;
	// pthread_t		monitor_thread;
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
	printf("here_is\n");
	// pthread_create(&monitor_thread, NULL, monitor_philos, (void *)&sim);
	// pthread_join(monitor_thread, NULL);
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
