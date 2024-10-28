/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaroslav <yaroslav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:01:46 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/28 17:24:36 by yaroslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		print_msg(philo, "fork_left");
		pthread_mutex_lock(philo->right_fork);
		print_msg(philo, "fork_right");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_msg(philo, "fork_right");
		pthread_mutex_lock(philo->left_fork);
		print_msg(philo, "fork_left");
	}
}

int	philo_eaten(t_philo *philo)
{
	int	i;

	i = philo->sim->numbers_of_philosophers;
	while (i > 0)
	{
		if (philo[i].left_fork && philo[i].right_fork)
		{
			philo->meals_eaten++;
			i--;
		}
		if (i == 0)
			return (1);
		continue ;
	}
	return (0);
}

int	eat(t_philo *philo)
{
	if (if_one_philo(philo))
		return (1);
	take_forks(philo);
	print_msg(philo, "eating");
	ft_usleep(philo->sim->time_to_eat);
	philo_eaten(philo);
	// philo->meals_eaten++;
	// if (philo->sim->number_meals != -1
	// 	&& philo->meals_eaten
	// 	>= philo->sim->number_meals)
	// 	philo->sim->sim_terminated = 1;
	put_forks(philo);
	return (0);
}

void	sleep_philo(t_philo *philo)
{
	print_msg(philo, "sleeping");
	ft_usleep(philo->sim->time_to_sleep);
}

int	think(t_philo *philo)
{
	print_msg(philo, "thinking");
	// ft_usleep(philo->sim->time_to_sleep);
	ft_usleep(1);
	return (1);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
