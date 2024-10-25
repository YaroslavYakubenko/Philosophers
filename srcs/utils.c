/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:50:59 by yyakuben          #+#    #+#             */
/*   Updated: 2024/10/25 23:12:09 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int				num;
	int				i;
	int				np;

	np = 1;
	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == '\n' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			np = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return ((np * num));
}

int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

long	get_current_time(struct timeval time)
{
	struct timeval	now;

	gettimeofday(&time, NULL);
	return (((now.tv_sec * 1000) + (now.tv_usec / 1000))
		- ((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	ft_sleep(int time)
{
	struct timeval	start_time;
	struct timeval	now;
	int				diff;

	gettimeofday(&start_time, NULL);
	while (1)
	{
		gettimeofday(&now, NULL);
		diff = ((now.tv_sec * 1000) + (now.tv_usec / 1000))
			- ((start_time.tv_sec * 1000) + (start_time.tv_usec / 1000));
		if (diff >= time)
			break ;
		usleep(100);
	}
}
