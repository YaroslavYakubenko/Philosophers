/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:27:28 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/26 20:14:45 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_fork(t_philo *philo, char *msg)
{
	if (ft_strcmp(msg, "fork_left") == 0)
		printf("%ld %d has taken a left fork\n",
			get_current_time(philo->sim->time), philo->id);
	else if (ft_strcmp(msg, "fork_right") == 0)
		printf("%ld %d has taken a right fork\n",
			get_current_time(philo->sim->time), philo->id);
	// printf("here\n");
}

void	print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->print_mutex);
	// if (philo->sim->is_die)
	// {
	// 	pthread_mutex_unlock(&philo->print_mutex);
	// 	return ;
	// }
	// printf("here\n");
	print_fork(philo, msg);
	if (ft_strcmp(msg, "eating") == 0)
		printf("%ld %d is eating\n", get_current_time(philo->sim->time),
			philo->id);
	else if (ft_strcmp(msg, "sleeping") == 0)
		printf("%ld %d is sleeping\n", get_current_time(philo->sim->time),
			philo->id);
	else if (ft_strcmp(msg, "thinking") == 0)
		printf("%ld %d is thinking\n", get_current_time(philo->sim->time),
			philo->id);
	else if (ft_strcmp(msg, "died") == 0)
	{
		printf("%ld %d has died\n", get_current_time(philo->sim->time),
			philo->id);
		philo->sim->is_die = 1;
	}
	pthread_mutex_unlock(&philo->print_mutex);
}
