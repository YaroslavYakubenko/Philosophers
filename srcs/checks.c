/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:28:32 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/26 21:24:02 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	validate_arguments(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	while (i < ac)
	{
		if (!is_valid_number(av[i]))
		{
			printf("Error: wrong argument\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_philo_status(t_philo *philo, long time)
{
	if (time >= philo->sim->time_to_die || philo->sim->is_die == 1)
	{
		print_msg(philo, "died");
		return (1);
	}
	return (0);
}

void	check_philo_meals(t_simulation *sim)
{
	int	i;
	int	all_fed;

	while (1)
	{
		all_fed = 1;
		i = 0;
		while (i < sim->numbers_of_philosophers)
		{
			if (sim->philos[i].meals_required != -1
				&& sim->philos[i].meals_eaten < sim->philos[i].meals_required)
			{
				all_fed = 0;
				break ;
			}
			i++;
		}
		if (all_fed == 0)
		{
			// pthread_mutex_lock(&sim->philos[0].print_mutex);
			// printf("All philosophers have eaten the required number of meals.\n");
			// pthread_mutex_unlock(&sim->philos[0].print_mutex);
			sim->sim_terminated = 1;
			break ;
		}
		usleep(1000);
	}
}

int	if_one_philo(t_philo *philo)
{
	if (philo->sim->numbers_of_philosophers == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_msg(philo, "fork_left");
		ft_usleep(philo->sim->time_to_die);
		print_msg(philo, "died");
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

void	take_forks_in_the_line(t_philo *philo)
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
