/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:34:28 by jmatheis          #+#    #+#             */
/*   Updated: 2022/12/12 14:52:55 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	all_actions(t_ph *ph, t_thread *thread)
{
	if (pthread_mutex_lock(&ph->forks[thread->left]) < 0)
		error_return(NULL, "locking error");
	print_action(ph, thread, "fork");
	if (pthread_mutex_lock(&ph->forks[thread->right]) < 0)
		error_return(NULL, "locking error");
	print_action(ph, thread, "fork");
	thread->last_meal = ph->new_time;
	print_action(ph, thread, "eating");
	thread->no_meals += 1;
	ft_usleep(ph->eat_time);
	ph->new_time = timestamp(ph);
	thread->last_meal = ph->new_time;
	if (pthread_mutex_unlock(&ph->forks[thread->left]) < 0)
		error_return(NULL, "unlocking error");
	if (pthread_mutex_unlock(&ph->forks[thread->right]) < 0)
		error_return(NULL, "unlocking error");
	print_action(ph, thread, "sleeping");
	ft_usleep(ph->sleep_time);
	ph->new_time = timestamp(ph);
	print_action(ph, thread, "thinking");
}

void	print_action(t_ph *ph, t_thread *thread, char *str)
{
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
		exit (0);
	}
	return (1);
}

int	check_death(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < ph->philos)
	{
		if  (ph->new_time - ph->thread[i]->last_meal > (unsigned int)ph->die_time)
		{
			ph->stop = -1;
			print_action(ph, ph->thread[i], "died");
			exit (0); //return here to free everything correctly
		}
		i++;
	}
	return (1);
}
