/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:34:28 by jmatheis          #+#    #+#             */
/*   Updated: 2022/12/09 14:18:55 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_ph *ph, t_thread *thread)
{
	if (pthread_mutex_lock(&ph->forks[thread->left]) < 0)
		error_return(NULL, "locking error");
	print_action(ph, thread, "fork");
	if (pthread_mutex_lock(&ph->forks[thread->right]) < 0)
		error_return(NULL, "locking error");
	print_action(ph, thread, "fork");
}

void	putdown_forks(t_ph *ph, t_thread *thread)
{
	if (pthread_mutex_unlock(&ph->forks[thread->left]) < 0)
		error_return(NULL, "unlocking error");
	if (pthread_mutex_unlock(&ph->forks[thread->right]) < 0)
		error_return(NULL, "unlocking error");
}

void	eating(t_ph *ph, t_thread *thread)
{
	ph->thread[ph->iter]->last_meal = timestamp(ph);
	print_action(ph, thread, "eating");
	ph->thread[ph->iter]->no_meals += 1;
	usleep(ph->eat_time * 1000);
}

void	sleeping(t_ph *ph, t_thread *thread)
{
	print_action(ph, thread, "sleeping");
	usleep(ph->sleep_time * 1000);
}

void	print_action(t_ph *ph, t_thread *thread, char *str)
{
	if (str[0] != 'f')
		ph->new_time = timestamp(ph);
	if (str[0] == 'f')
		printf("%d\t%d has taken a %s\n", ph->new_time, thread->ph_id, str);
	else if (str[0] == 'd')
		printf("%d\t%d has %s\n", ph->new_time, thread->ph_id, str);
	else
		printf("%d\t%d is %s\n", ph->new_time, thread->ph_id, str);
}

int	check_last_meal(t_ph *ph)
{
	int	i;

	i = 0;
	if (ph->no_of_meals != -1)
	{
		while(i < ph->philos)
		{
			if (ph->thread[i]->no_meals < ph->no_of_meals)
				return (1);
			i++;
		}
		ph->stop = -1;
		printf("end of simulation\n");
		return (0);
	}
	return (1);
}

int	check_death(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < ph->philos)
	{
		if  ((timestamp(ph) - ph->thread[i]->last_meal) > ph->die_time)
		{
			ph->stop = -1;
			print_action(ph, ph->thread[i], "died");
			exit (0); //return here to free everything correctly
		}
		i++;
	}
	return (1);
}