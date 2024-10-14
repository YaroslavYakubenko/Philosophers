/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:44:44 by yaroslav          #+#    #+#             */
/*   Updated: 2024/10/14 20:36:50 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id; // номер философа
	pthread_t		thread; // поток философа
	pthread_mutex_t	*left_fork; // указатель на левую вилку
	pthread_mutex_t	*right_fork; // указатель на правую вилку
}	t_philo;

typedef struct s_table
{
	int				num_philo; // количество философов
	t_philo			*philo; // масив философов
	pthread_mutex_t	*forks; // масив вилок
}	t_table;

int		validate_arguments(int ac, char **av);


#endif