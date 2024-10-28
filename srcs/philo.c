/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaroslav <yaroslav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:33:29 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/28 17:36:40 by yaroslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_is_finished(t_philo *philo)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (1)
	{
		if (philo[i].meals_eaten >= philo->sim->numbers_of_philosophers)
			j++;
			i++;
		if (j == philo->sim->numbers_of_philosophers)
		{
			philo->sim->sim_terminated = 1;
			return (1);
		}
		continue ;
	}
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
		if (philo_is_finished(philo))
			break ;
		philo->last_meal_time = get_current_time(philo->sim->time);
		sleep_philo(philo);
		think(philo);
	}
	return (NULL);
}
