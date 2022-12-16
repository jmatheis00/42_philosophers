/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:34:34 by jmatheis          #+#    #+#             */
/*   Updated: 2022/12/16 12:06:19 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// locking to avoid data races
int	print_action(t_ph *ph, t_thread *thread, char *str)
{
	if (pthread_mutex_lock(&ph->print_mutex) < 0)
	{
		printf("locking error\n");
		return (1);
	}
	ph->new_time = timestamp(ph);
	if (str[0] == 'f')
		printf("%d\t%d has taken a %s\n", ph->new_time, thread->ph_id, str);
	else if (str[0] == 'd')
		printf("%d\t%d has %s\n", ph->new_time, thread->ph_id, str);
	else
		printf("%d\t%d is %s\n", ph->new_time, thread->ph_id, str);
	if (pthread_mutex_unlock(&ph->print_mutex) < 0)
	{
		printf("locking error\n");
		return (1);
	}
	return (0);
}

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
