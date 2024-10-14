/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 22:22:26 by yaroslav          #+#    #+#             */
/*   Updated: 2024/10/14 21:47:34 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_simulation	sim;

	if (!validate_arguments(ac, av))
		return (1);
	if (!init_simulation(&sim, ac, av))
		return (1);
	free(sim.philos);
	free(sim.forks);
	return (0);
}
