/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:34:28 by jmatheis          #+#    #+#             */
/*   Updated: 2022/12/16 12:06:13 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eating(t_ph *ph, t_thread *thread)
{
	if (pthread_mutex_lock(&ph->forks[thread->left]) < 0)
	{
		printf("locking error\n");
		return (1);		
	}
	if (print_action(ph, thread, "fork"))
		return (1);
	if (pthread_mutex_lock(&ph->forks[thread->right]) < 0)
	{
		printf("locking error\n");
		return (1);		
	}
	if (print_action(ph, thread, "fork"))
		return (1);
	thread->last_meal = ph->new_time;
	if (print_action(ph, thread, "eating"))
		return (1);
	thread->no_meals += 1;
	ft_usleep(ph->eat_time);
	thread->last_meal = ph->new_time;
	return (0);
}

static int	all_actions(t_ph *ph, t_thread *thread)
{
	if (eating(ph, thread))
		return (1);
	if (pthread_mutex_unlock(&ph->forks[thread->left]) < 0)
	{
		printf("unlocking error\n");
		return (1);			
	}
	if (pthread_mutex_unlock(&ph->forks[thread->right]) < 0)
	{
		printf("locking error\n");
		return (1);	
	}
	if (print_action(ph, thread, "sleeping"))
		return (1);
	ft_usleep(ph->sleep_time);
	if (print_action(ph, thread, "thinking"))
		return (1);
	return (0);
}

static void	*routine(void *arg)
{
	t_ph	*ph;
	int		tmp;

	ph = (t_ph *)arg;
	tmp = ph->iter;
	ph->iter++;
	get_starttime(ph);
	if (tmp % 2 == 0)
	{
		if (print_action(ph, ph->thread[tmp], "thinking"))
			return (NULL);
		ft_usleep(ph->eat_time);
	}
	while (ph->stop != -1)
	{
		if (all_actions(ph, ph->thread[tmp]))
			return (NULL);
	}
	return (NULL);
}

static void	create_mutexes(t_ph *ph, t_thread **thread)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&ph->print_mutex, NULL))
	{
		printf("Error occured\n");
		free_structs(ph, thread);
		exit (1);
	}
	while (i < ph->philos)
	{
		if (pthread_mutex_init(&ph->forks[i], NULL))
		{
			printf("Error occured\n");
			free_structs(ph, thread);
			exit (1);
		}
		i++;
	}
}

// pthread_join: waits until death thread returns
// pthread_detach
void	start_routine(t_ph *ph, t_thread **thread)
{
	int	i;

	i = 0;
	create_mutexes(ph, thread);
	while (i < ph->philos)
	{
		if (pthread_create(&thread[i]->id, NULL, &routine, ph))
		{
			printf("Error occured\n");
			free_structs(ph, ph->thread);
			exit (1);
		}
		i++;
	}
	if (pthread_create(&ph->death_thr, NULL, &deathcheck, ph))
	{
		printf("Error occured\n");
		free_structs(ph, ph->thread);
		exit (1);
	}
	pthread_join(ph->death_thr, NULL);
}
