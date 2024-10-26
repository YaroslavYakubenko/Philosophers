/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:01:46 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/26 21:25:26 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		if (pthread_mutex_lock(philo->right_fork) == 0)
			break ;
		pthread_mutex_unlock(philo->left_fork);
		ft_usleep(100);
	}
	print_msg(philo, "fork_left");
	print_msg(philo, "fork_right");
	return (1);
}

int	eat(t_philo *philo)
{
	if (if_one_philo(philo))
		return (1);
	take_forks_in_the_line(philo);
	print_msg(philo, "eating");
	philo->last_meal_time = get_current_time(philo->sim->time);
	philo->meals_eaten++;
	if (philo->sim->number_of_times_each_philosopher_must_eat != -1
		&& philo->meals_eaten
		>= philo->sim->number_of_times_each_philosopher_must_eat)
		philo->sim->sim_terminated = 1;
	ft_usleep(philo->sim->time_to_eat * 1000);
	put_forks(philo);
	return (0);
}

void	sleep_philo(t_philo *philo)
{
	print_msg(philo, "sleeping");
	ft_usleep(philo->sim->time_to_sleep * 1000);
}

int	think(t_philo *philo)
{
	print_msg(philo, "thinking");
	ft_usleep(philo->sim->time_to_sleep * 1000);
	return (1);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
