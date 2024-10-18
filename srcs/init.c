/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:14:15 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/18 22:28:54 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->numbers_of_philosophers)
	{
		pthread_mutex_init(&sim->forks[i], NULL);
		i++;
	}
	return (1);
}

int	init_philosophers(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->numbers_of_philosophers)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].meals_eaten = 0;
		if (sim->number_of_times_each_philosopher_must_eat != -1)
			sim->philos[i].meals_required = -1;
		else
			sim->philos[i].meals_required
				= sim->number_of_times_each_philosopher_must_eat;
		sim->philos[i].last_meal_time = 0;
		sim->philos[i].left_fork = &sim->forks[i];
		sim->philos[i].right_fork = &sim->forks[(i + 1)
			% sim->numbers_of_philosophers];
		sim->philos[i].sim = sim;
		pthread_mutex_init(&sim->philos[i].print_mutex, NULL);
		i++;
	}
	return (1);
}

int	init_alive_status(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->is_alive = malloc(sizeof(int) * sim->numbers_of_philosophers);
	while (i < sim->numbers_of_philosophers)
	{
		sim->is_alive[i] = 1;
		i++;
	}
	return (1);
}
	// printf("here\n");

int	init_simulation(t_simulation *sim, int ac, char **av)
{
	sim->numbers_of_philosophers = ft_atoi(av[1]);
	sim->time_to_die = ft_atoi(av[2]);
	sim->time_to_eat = ft_atoi(av[3]);
	sim->time_to_sleep = ft_atoi(av[4]);
	sim->number_of_times_each_philosopher_must_eat = -1;
	if (ac == 6)
		sim->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	sim->philos = malloc(sizeof(t_philo) * sim->numbers_of_philosophers);
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->numbers_of_philosophers);
	if (!sim->philos || !sim->forks)
		return (0);
	init_forks(sim);
	init_philosophers(sim);
	sim->start_time = get_current_time();
	if (!init_alive_status(sim))
		return (0);
	return (1);
}
