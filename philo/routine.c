/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:34:28 by jmatheis          #+#    #+#             */
/*   Updated: 2022/12/15 12:49:41 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// locking to avoid data races
void	print_action(t_ph *ph, t_thread *thread, char *str)
{
	if (pthread_mutex_lock(&ph->print_mutex) < 0)
		error_return(NULL, "locking error");
	ph->new_time = timestamp(ph);
	if (str[0] == 'f')
		printf("%d\t%d has taken a %s\n", ph->new_time, thread->ph_id, str);
	else if (str[0] == 'd')
		printf("%d\t%d has %s\n", ph->new_time, thread->ph_id, str);
	else
		printf("%d\t%d is %s\n", ph->new_time, thread->ph_id, str);
	if (pthread_mutex_unlock(&ph->print_mutex) < 0)
		error_return(NULL, "locking error");
}

static void	all_actions(t_ph *ph, t_thread *thread)
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
	thread->last_meal = ph->new_time;
	if (pthread_mutex_unlock(&ph->forks[thread->left]) < 0)
		error_return(NULL, "unlocking error");
	if (pthread_mutex_unlock(&ph->forks[thread->right]) < 0)
		error_return(NULL, "unlocking error");
	print_action(ph, thread, "sleeping");
	ft_usleep(ph->sleep_time);
	print_action(ph, thread, "thinking");
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
		print_action(ph, ph->thread[tmp], "thinking");
		ft_usleep(ph->eat_time);
	}
	while (ph->stop != -1)
		all_actions(ph, ph->thread[tmp]);
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
