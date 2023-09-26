/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:43:00 by jmatheis          #+#    #+#             */
/*   Updated: 2023/09/26 02:23:39 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_last_meal(t_ph *ph)
{
	int	i;

	i = 0;
	if (ph->no_of_meals != -1)
	{
		while (i < ph->philos)
		{
			if (ph->thread[i]->no_meals < ph->no_of_meals)
				return (1);
			i++;
		}
		ph->stop = -1;
		usleep(200);
		printf("end of simulation\n");
		return (0);
	}
	return (1);
}

static int	check_death(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < ph->philos)
	{
		if (timestamp(ph) - ph->thread[i]->last_meal
			>= ph->die_time)
		{
			ph->stop = -1;
			usleep(500);
			if (print_action(ph, ph->thread[i], "died"))
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

void	*deathcheck(void *arg)
{
	t_ph	*ph;

	ph = (t_ph *)arg;
	while (1)
	{
		if (!check_last_meal(ph) || !check_death(ph))
			return (NULL);
	}
	return (NULL);
}
