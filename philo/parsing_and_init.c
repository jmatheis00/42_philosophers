/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_and_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:59:04 by jmatheis          #+#    #+#             */
/*   Updated: 2022/12/13 15:58:30 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_arguments(int ac, char **ag)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (ac < 5 || ac > 6)
	{
		printf("invalid number of arguments\n");
		return (1);
	}
	while (ag[i])
	{
		while (ag[i][j])
		{
			if (!ft_isdigit(ag[i][j]))
			{
				printf("check argument number %d\n", i);
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

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
		thread[i]->ph_id = i + 1;
		i++;
	}
	thread[i] = NULL;
	return (thread);
}

t_ph	*init_ph(t_ph *ph, char **ag)
{
	ph = malloc(1 * sizeof(t_ph));
	if (!ph)
		error_return(NULL, "allocation error");
	ph->philos = ft_atoi(ag[1]);
	if (ph->philos < 1)
		error_return(NULL, "invalid no. of philosophers");
	ph->die_time = ft_atoi(ag[2]);
	ph->eat_time = ft_atoi(ag[3]);
	ph->sleep_time = ft_atoi(ag[4]);
	ph->no_of_meals = -1;
	ph->iter = 0;
	ph->stop = 0;
	if (ag[5])
		ph->no_of_meals = ft_atoi(ag[5]);
	ph->forks = malloc(sizeof(pthread_mutex_t) * ph->philos);
	if (!ph->forks)
		error_return(NULL, "allocation error");
	ph->death_thr = 0;
	ph->old_time = 0;
	ph->new_time = 0;
	return (ph);
}
