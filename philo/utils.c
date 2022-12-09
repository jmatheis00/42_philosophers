/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:34:34 by jmatheis          #+#    #+#             */
/*   Updated: 2022/12/09 14:17:30 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_starttime(t_ph *ph)
{
	struct timeval	before;

	gettimeofday(&before, NULL);
	ph->old_time = ((before.tv_sec) * 1000) + ((before.tv_usec) / 1000);
}

int	timestamp(t_ph *ph)
{
	struct timeval	after;
	int				time;

	gettimeofday(&after, NULL);
	time = ((after.tv_sec) * 1000) + ((after.tv_usec) / 1000);
	time = time - ph->old_time;
	return (time);
}

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
