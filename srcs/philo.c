/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:33:29 by yyakuben          #+#    #+#             */
/*   Updated: 2024/11/05 18:45:17 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eaten(t_philo *philo)
{
	t_simulation	*sim;

	pthread_mutex_lock(&philo->sim->print_mutex);
	sim = philo->sim;
	if (philo->left_fork && philo->right_fork)
	{
		philo->meals_eaten++;
	}
	pthread_mutex_unlock(&philo->sim->print_mutex);
}

int	philo_is_finished(t_philo *philo)
{
	t_simulation	*sim;
	int				i;
	int				finished_philo;

	finished_philo = 0;
	i = 0;
	sim = philo->sim;
	pthread_mutex_lock(&sim->print_mutex);
	while (i < sim->numbers_of_philosophers)
	{
		if (sim->philos[i].meals_eaten >= sim->number_meals)
		{
			philo->finished_eating++;
		}
		i++;
	}
	if (philo->finished_eating == sim->numbers_of_philosophers)
	{
		sim->sim_terminated = 1;
		pthread_mutex_unlock(&sim->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&sim->print_mutex);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		print_msg(philo, "thinking");
		ft_usleep(philo->sim->time_to_eat);
	}
	while (1)
	{
		if (eat(philo))
			philo->sim->is_die = 1;
		time = get_current_time(philo->sim->time) - philo->last_meal_time;
		if (check_philo_status(philo, time))
			break ;
		philo->last_meal_time = get_current_time(philo->sim->time);
		sleep_philo(philo);
		think(philo);
	}
	return (NULL);
}
