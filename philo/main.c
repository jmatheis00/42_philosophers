/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 09:46:29 by jmatheis          #+#    #+#             */
/*   Updated: 2022/12/08 16:26:01 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo
// no_of_philos
// time_to_die
// time_to_eat
// time_to_sleep
// [no_of_times_each_philo_must_eat]
void	get_starttime(t_ph *ph)
{
	struct timeval	before;

	gettimeofday(&before, NULL);
	ph->old_time = ((before.tv_sec) * 1000) + ((before.tv_usec) / 1000);
	ph->new_time = timestamp(ph);
}

void	*routine(void *arg)
{
	t_ph *ph;
	int temp;

	ph = (t_ph *)arg;
	get_starttime(ph);
	// if (ph->iter % 2 == 0)
	// {
	// 	take_forks(ph);
	// 	eating(ph);
	// }
	temp = ph->iter;
	while(1)
	{
		printf("HELLO FROM %i\n", temp);
		usleep(1000000);
		// ph->new_time = timestamp(ph);
		// sleeping(ph);
		// ph->new_time = timestamp(ph);
		// if (ph->sleep_time < ph->eat_time)
		// 	thinking(ph);
		// ph->new_time = timestamp(ph);
		// take_forks(ph);
		// eating(ph);		
		// if (ph->no_of_meals != -1 && check_last_meal(ph) == 0)
		// {
		// 	printf("end of simulation\n");
		// 	exit(0);	
		// }
	}
	return (NULL);
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

void	start_routine(t_ph *ph, t_thread **thread)
{
	ph->iter = 0;
	while (ph->thread[ph->iter] && ph->iter < ph->philos)
	{
		if (pthread_create(&thread[ph->iter]->id, NULL, &routine, ph))
		{
			printf("Error occured\n");
			free_structs(ph, thread);
			exit (1);
		}
		usleep(1000);
		ph->iter++;
	}
}

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
		timestamp(ph);
		start_routine(ph, ph->thread);
		usleep(10000000);
	}
	// death thread
	// main funktion läuft ansonsten weiter (return(0))
	// mit death thread in while loop nicht
	else
		free_structs(ph, ph->thread);
	return (0);
}
