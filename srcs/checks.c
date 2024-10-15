/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:28:32 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/15 19:32:36 by yyakuben         ###   ########.fr       */
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

void	check_philo_status(t_simulation *sim)
{
	int		i;
	long	current_time;

	i = 0;
	while (1)
	{
		current_time = get_current_time();
		while (i < sim->numbers_of_philosophers)
		{			
			pthread_mutex_lock(&sim->philos[i].print_mutex);
			if (current_time - sim->philos[i].last_meal_time > sim->time_to_die)
			{
				sim->is_alive[i] = 0;
				printf("%ld %d has died\n", current_time - sim->start_time,
					sim->philos[i].id);
				pthread_mutex_unlock(&sim->philos[i].print_mutex);
				return ;
			}
			pthread_mutex_unlock(&sim->philos[i].print_mutex);
			i++;
		}
		usleep(1000);
	}
}
