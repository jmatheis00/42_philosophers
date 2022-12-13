/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:34:34 by jmatheis          #+#    #+#             */
/*   Updated: 2022/12/13 14:51:27 by jmatheis         ###   ########.fr       */
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

void	ft_usleep(long stop)
{
	struct timeval	before;
	long			starttime;
	long			diff;

	gettimeofday(&before, NULL);
	starttime = ((before.tv_sec) * 1000) + ((before.tv_usec) / 1000);
	diff = 0;
	while (diff < stop)
	{
		usleep(100);
		gettimeofday(&before, NULL);
		diff = ((before.tv_sec) * 1000) + ((before.tv_usec) / 1000) - starttime;
	}
}
