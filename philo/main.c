/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 09:46:29 by jmatheis          #+#    #+#             */
/*   Updated: 2022/12/01 14:58:57 by jmatheis         ###   ########.fr       */
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

void *sleeping(int i)
{
	printf("timestamp: philo %d is sleeping\n", i);
	return (NULL);
}


void create_threads(t_ph *ph)
{
	int	i;
	pthread_t philo_id[ph->philos];

	i = 0;
	while (i < ph->philos)
	{
		if (pthread_create(&philo_id[i], NULL, &action, NULL))
		{
			printf("Error occured\n");
			return ;		
		}
		if (i % 2 == 0)
			printf("timestamp: philo %d is sleeping\n", i);
		else
			printf("timestamp: philo %d is eating\n", i);
		i++;
	}
}

int	main(int ac, char **ag)
{
	t_ph	*ph;

	struct timeval ms;

	ph = malloc(1 * sizeof(t_ph));
	if (!ph)
		return (1);
	memset(ph, 0, sizeof(t_ph));
	if (check_arguments(ac, ag) || init_struct(ph, ag))
		return (1);
	gettimeofday(&ms, NULL);
	unsigned int start_time = ((ms.tv_sec * 1000) + (ms.tv_usec)/ 1000);
	// printf("TIME: seconds %ld microseconds %d\n", ms.tv_sec, ms.tv_usec);
	printf("START TIME: %d\n", start_time);
	// while ((get_time() - start_time) < time_in_ms)
	// 	usleep(time_in_ms / 10);
	// RESET TIMESTAMP ???
	if (ph->philos % 2 == 0)
	{
		create_threads(ph);
	}
	else
		printf("unequal no. of philos\n");
	return (0);
}
