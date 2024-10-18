/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaroslav <yaroslav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:33:29 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/18 15:57:30 by yaroslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->print_mutex);
	printf("%ld %d has taken a left fork\n", get_current_time()
		- philo->sim->start_time, philo->id);
	pthread_mutex_unlock(&philo->print_mutex);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->print_mutex);
	printf("%ld %d has taken a right fork\n", get_current_time()
		- philo->sim->start_time, philo->id);
	pthread_mutex_unlock(&philo->print_mutex);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->print_mutex);
	printf("%ld %d is eating\n", get_current_time()
		- philo->sim->start_time, philo->id);
	pthread_mutex_unlock(&philo->print_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	if (philo->sim->number_of_times_each_philosopher_must_eat != -1
		&& philo->meals_eaten >= philo->sim->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philo->print_mutex);
		printf("%ld %d is done eating\n", get_current_time()
			- philo->sim->start_time, philo->id);
		pthread_mutex_unlock(&philo->print_mutex);
	}
		// philo->sim->is_alive[philo->id - 1] = 0;
	usleep(philo->sim->time_to_eat * 1000);
}

void	sleep_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->print_mutex);
	printf("%ld %d is sleeping\n", get_current_time()
		- philo->sim->start_time, philo->id);
	pthread_mutex_unlock(&philo->print_mutex);
	usleep(philo->sim->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->print_mutex);
	printf("%ld %d is thinking\n", get_current_time()
		- philo->sim->start_time, philo->id);
	pthread_mutex_unlock(&philo->print_mutex);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// printf("here\n");
	while (!philo->sim->sim_terminated)
	{
		think(philo);
		take_forks(philo);
		eat(philo);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		sleep_philo(philo);
	}
	return (NULL);
}
