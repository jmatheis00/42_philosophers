/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 09:46:29 by jmatheis          #+#    #+#             */
/*   Updated: 2022/12/05 22:06:14 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo
// no_of_philos
// time_to_die
// time_to_eat
// time_to_sleep
// [no_of_times_each_philo_must_eat]

void *action()
{
	return (NULL);
}

int	timestamp()
{
	struct timeval after;
	int	time;

	gettimeofday(&after, NULL);
	time = ((after.tv_sec) * 1000) + ((after.tv_usec) / 1000);
	return (time);
}

void	create_threads(t_ph *ph, t_thread **thread)
{
	int				i;

	i = 0;
	while (i < ph->philos)
	{
		if (pthread_mutex_init(&ph->forks[i], NULL) 
			|| pthread_create(&thread[i]->id, NULL, &action, NULL))
		{
			// free
			printf("Error occured\n");
			exit (1);
		}
		i++;
	}
}


void print_thread(t_thread **thread)
{
    int i;

    i = 0;
    while (thread[i])
    {
        printf("left fork thread: %d %d\n", i, thread[i]->left);
        printf("right fork thread: %d %d\n", i, thread[i]->right);
        i++;
    }
}

int	main(int ac, char **ag)
{
	t_ph	*ph;
	t_thread **thread;

	thread = NULL;
	ph = NULL;
	if (check_arguments(ac, ag))
		return (1);
	ph = init_ph(ph, ag);
	thread = init_thread(ph, thread);
	if (ph && thread)
	{
		print_thread(thread);
		// create_threads(ph, thread);
	}
	else
		free_structs(ph, thread);
	return (0);
}
