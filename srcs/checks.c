/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:28:32 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/27 20:25:17 by yyakuben         ###   ########.fr       */
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
	// printf("time: %ld\n", time);
	// printf("time_to_die: %d\n", philo->sim->time_to_die);
	// printf("is_die: %d\n", philo->sim->is_die);
	if (time >= philo->sim->time_to_die || philo->sim->is_die == 1)
	{
		print_msg(philo, "died");
		return (1);
	}
	return (0);
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
