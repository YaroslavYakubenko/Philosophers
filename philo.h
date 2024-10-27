/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:44:44 by yaroslav          #+#    #+#             */
/*   Updated: 2024/10/27 20:45:40 by yyakuben         ###   ########.fr       */
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
	pthread_t			thread; // поток философа
	int					meals_eaten; // количество приемов пищи
	int					meals_required; // количество пищи который должен съесть
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
	int				number_meals; // количество приемов пищи
	// int				*is_alive; // массив флагов жизни философов
	int				is_die; // флаг для смерти
	int				sim_terminated; // флаг для завершения симуляции
	long			start_time; // время начала симуляции
	t_philo			*philos; // массив философов
	struct timeval	time; // структура времени
	pthread_mutex_t	*forks; // массив вилок
}	t_simulation;

int		ft_atoi(const char *str);
int		ft_strcmp(const char *str1, const char *str2);
long	get_current_time(struct timeval time);
int		validate_arguments(int ac, char **av);
int		init_simulation(t_simulation *sim, int ac, char **av);
void	take_forks(t_philo *philo);
int		eat(t_philo *philo);
void	sleep_philo(t_philo *philo);
int		think(t_philo *philo);
void	put_forks(t_philo *philo);
void	*philo_routine(void *arg);
int		check_philo_status(t_philo *philo, long time);
void	ft_usleep(int time);
int		if_one_philo(t_philo *philo);
void	print_msg(t_philo *philo, char *msg);

#endif