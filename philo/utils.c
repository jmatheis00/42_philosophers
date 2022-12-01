/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:34:34 by jmatheis          #+#    #+#             */
/*   Updated: 2022/12/01 13:25:27 by jmatheis         ###   ########.fr       */
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
	{
		i++;
	}
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

int	init_struct(t_ph *ph, char **ag)
{
	int	i;

	i = 0;
	ph->philos = ft_atoi(ag[1]);
	if (ph->philos < 2)
	{
		free (ph);
		printf("invalid no. of philosophers\n");
		return (1);
	}
	ph->die_time = ft_atoi(ag[2]);
	ph->eat_time = ft_atoi(ag[3]);
	ph->sleep_time = ft_atoi(ag[4]);
	if (ag[5])
		ph->no_of_meals = ft_atoi(ag[5]);
	return (0);
}