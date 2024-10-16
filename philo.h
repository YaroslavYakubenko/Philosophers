/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:44:44 by yaroslav          #+#    #+#             */
/*   Updated: 2024/10/16 21:22:00 by yyakuben         ###   ########.fr       */
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
	int					id; // номер философа
	int					meals_eaten; // количество приемов пищи
	int					meals_required; // cчётчик приёмов пищи
	long				last_meal_time; // время последнего приема пищи
	pthread_mutex_t		*left_fork; // указатель на левую вилку
	pthread_mutex_t		*right_fork; // указатель на правую вилку
	pthread_mutex_t		print_mutex; // мьютекс для печати
	struct s_simulation	*sim; // указатель на структуру симуляции
}	t_philo;

typedef struct s_simulation
{
	int				numbers_of_philosophers; // количество философов
	int				time_to_die; // время до смерти
	int				time_to_eat; // время на еду
	int				time_to_sleep; // время на сон
	int				number_of_times_each_philosopher_must_eat;
	int				*is_alive; // массив флагов жизни философов
	long			start_time; // время начала симуляции
	t_philo			*philos; // массив философов
	pthread_mutex_t	*forks; // массив вилок
	// pthread_mutex_t	*print_mutex; // мьютекс для печати
}	t_simulation;

int		ft_atoi(const char *str);
long	get_current_time(void);
int		validate_arguments(int ac, char **av);
int		init_simulation(t_simulation *sim, int ac, char **av);
void	*philo_routine(void *arg);
void	check_philo_status(t_simulation *sim);
void	check_philo_meals(t_simulation *sim);

#endif