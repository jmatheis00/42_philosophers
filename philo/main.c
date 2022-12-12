/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 09:46:29 by jmatheis          #+#    #+#             */
/*   Updated: 2022/12/12 14:58:20 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo
// no_of_philos
// time_to_die
// time_to_eat
// time_to_sleep
// [no_of_times_each_philo_must_eat]

// usleep() --> calling thread sleeps
void	*routine(void *arg)
{
	t_ph	*ph;
	int		tmp;

	ph = (t_ph *)arg;
	tmp = ph->iter;
	ph->iter++;
	get_starttime(ph);
	if (ph->philos < 2)
		return (NULL);
	if (tmp % 2 == 0)
	{
		print_action(ph, ph->thread[tmp], "thinking");
		ft_usleep(ph->eat_time);
	}
	while (ph->stop != -1)
		all_actions(ph, ph->thread[tmp]);
	return (NULL);
}

void	create_mutexes(t_ph *ph, t_thread **thread)
{
	int	i;

	i = 0;
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

void	*deathcheck(void *arg)
{
	t_ph	*ph;
	int		i;

	ph = (t_ph *)arg;
	i = 0;
	while (1)
	{
		if (!check_last_meal(ph) || !check_death(ph))
			exit (1);
	}
	return (NULL);
}

void	start_routine(t_ph *ph, t_thread **thread)
{
	int	i;

	i = 0;
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
	i = -1;
	while (++i < ph->philos)
		pthread_join(thread[i]->id, NULL);
}

// void	wait_for_threads(t_ph *ph, t_thread **thread)
// {
// 	int	i;

// 	i = 0;
// 	while (i < ph->philos)
// 	{
// 		pthread_join(thread[i]->id, NULL);
// 		i++;
// 	}
// }

// initialize thread in ph
// t_thread *thread is possible as well
// thread doesn't need to be allocated, just *thread
int	main(int ac, char **ag)
{
	t_ph		*ph;

	ph = NULL;
	if (check_arguments(ac, ag))
		return (1);
	ph = init_ph(ph, ag);
	ph->thread = init_thread(ph, ph->thread);
	if (ph && ph->thread)
	{
		create_mutexes(ph, ph->thread);
		start_routine(ph, ph->thread);
		// wait_for_threads(ph, ph->thread);
	}
	else
		free_structs(ph, ph->thread);
	return (0);
}

// death thread
// main funktion läuft ansonsten weiter (return(0))
// mit death thread in while loop nicht