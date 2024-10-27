/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:33:29 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/27 18:36:09 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (!eat(philo))
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
