/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:33:29 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/24 20:05:51 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->sim->time_to_eat * 1000);
	while (1)
	{
		if (philo->id % 2 == 1)
		{
			if (take_forks(philo))
			{
				eat(philo);
				sleep_philo(philo);
				usleep(100);
			}
			think(philo);
		}
		else
		{
			think(philo);
			if (take_forks(philo))
			{
				eat(philo);
				sleep_philo(philo);
				usleep(100);
			}
		}
	}
	return (NULL);
}
