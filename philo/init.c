/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:59:04 by jmatheis          #+#    #+#             */
/*   Updated: 2022/12/08 15:06:44 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	numb;

	i = 0;
	numb = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\t' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		numb = 10 * numb + (str[i] - 48);
		i++;
	}
	return (numb * sign);
}

t_thread	**init_thread(t_ph *ph, t_thread **thread)
{
	int	i;

	i = 0;
	thread = malloc(sizeof(t_thread *) * (ph->philos + 1));
	if (!thread)
		error_return(NULL, "allocation error");
	while (i < ph->philos)
	{
		thread[i] = malloc(sizeof(t_thread) * 1);
		if (!thread[i])
			error_return(NULL, "allocation error");
		thread[i]->left = i;
		if (i == 0)
			thread[i]->right = ph->philos - 1;
		else
			thread[i]->right = i - 1;
		thread[i]->no_meals = 0;
		thread[i]->last_meal = 0;
		thread[i]->id = 0;
		i++;
	}
	thread[i] = NULL;
	return (thread);
}

t_ph	*init_ph(t_ph *ph, char **ag)
{
	ph = malloc(1 * sizeof(t_ph));
	if (!ph)
		return (NULL);
	ph->philos = ft_atoi(ag[1]);
	if (ph->philos < 2)
		error_return(NULL, "invalid no. of philosophers");
	ph->die_time = ft_atoi(ag[2]);
	ph->eat_time = ft_atoi(ag[3]);
	ph->sleep_time = ft_atoi(ag[4]);
	ph->no_of_meals = -1;
	if (ag[5])
		ph->no_of_meals = ft_atoi(ag[5]);
	ph->forks = malloc(sizeof(pthread_mutex_t) * ph->philos);
	if (!ph->forks)
		error_return(NULL, "allocation error");
	return (ph);
}
