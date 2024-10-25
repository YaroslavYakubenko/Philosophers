/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:01:46 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/25 22:54:34 by yyakuben         ###   ########.fr       */
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
		usleep(100);
	}
	print_msg(philo, "fork_left");
	print_msg(philo, "fork_right");
	return (1);
}

// int	take_forks(t_philo *philo)
// {
// 	if (philo->id % 2 == 0)
// 	{
// 		pthread_mutex_lock(philo->left_fork);
// 		pthread_mutex_lock(&philo->print_mutex);
// 		printf("%ld %d has taken a left fork\n", get_current_time()
// 			- philo->sim->start_time, philo->id);
// 		pthread_mutex_unlock(&philo->print_mutex);
// 		pthread_mutex_lock(philo->right_fork);
// 		pthread_mutex_lock(&philo->print_mutex);
// 		printf("%ld %d has taken a right fork\n", get_current_time()
// 			- philo->sim->start_time, philo->id);
// 		pthread_mutex_unlock(&philo->print_mutex);
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(philo->right_fork);
// 		pthread_mutex_lock(&philo->print_mutex);
// 		printf("%ld %d has taken a right fork\n", get_current_time()
// 			- philo->sim->start_time, philo->id);
// 		pthread_mutex_unlock(&philo->print_mutex);
// 		pthread_mutex_lock(philo->left_fork);
// 		pthread_mutex_lock(&philo->print_mutex);
// 		printf("%ld %d has taken a left fork\n", get_current_time()
// 			- philo->sim->start_time, philo->id);
// 		pthread_mutex_unlock(&philo->print_mutex);
// 	}
// 	return (1);
// }

int	eat(t_philo *philo)
{
	// printf("here\n");
	if (!if_one_philo(philo))
		return (1);
	print_msg(philo, "eating");
	philo->last_meal_time = get_current_time(philo->sim->time);
	philo->meals_eaten++;
	if (philo->sim->number_of_times_each_philosopher_must_eat != -1
		&& philo->meals_eaten
		>= philo->sim->number_of_times_each_philosopher_must_eat)
		philo->sim->sim_terminated = 1;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	usleep(philo->sim->time_to_eat * 1000);
	put_forks(philo);
	return (0);
}

void	sleep_philo(t_philo *philo)
{
	print_msg(philo, "sleeping");
	usleep(philo->sim->time_to_sleep * 1000);
}

int	think(t_philo *philo)
{
	print_msg(philo, "thinking");
	usleep(philo->sim->time_to_sleep * 1000);
	return (1);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
