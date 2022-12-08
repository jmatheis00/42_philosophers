/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:34:28 by jmatheis          #+#    #+#             */
/*   Updated: 2022/12/08 15:53:18 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_ph *ph)
{
	if (pthread_mutex_lock(&ph->forks[ph->thread[ph->iter]->left]) < 0)
		error_return(NULL, "locking error");
	print_action(ph, "fork");
	if (pthread_mutex_lock(&ph->forks[ph->thread[ph->iter]->right]) < 0)
		error_return(NULL, "locking error");
	print_action(ph, "fork");
}

void	eating(t_ph *ph)
{
	print_action(ph, "eating");
	ph->thread[ph->iter]->no_meals += 1;
	usleep(ph->eat_time * 1000);
	if (pthread_mutex_unlock(&ph->forks[ph->thread[ph->iter]->left]) < 0)
		error_return(NULL, "unlocking error");
	if (pthread_mutex_unlock(&ph->forks[ph->thread[ph->iter]->right]) < 0)
		error_return(NULL, "unlocking error");
}

void	sleeping(t_ph *ph)
{
	print_action(ph, "sleeping");
	ph->thread[ph->iter]->last_meal += ph->new_time;
	usleep(ph->sleep_time * 1000);
}

void	thinking(t_ph *ph)
{
	if (ph->sleep_time < ph->eat_time)
	{
		print_action(ph, "thinking");
		usleep((ph->eat_time - ph->sleep_time) * 1000);
	}
}

void	print_action(t_ph *ph, char *str)
{
	if (str[0] == 'f')
		printf("%d\t%d has taken a %s\n", ph->new_time, ph->iter, str);
	else if (str[0] == 'd')
		printf("%d\t%d has %s\n", ph->new_time, ph->iter, str);
	else
		printf("%d\t%d is %s\n", ph->new_time, ph->iter, str);
}

int	check_last_meal(t_ph *ph)
{
	int	i;

	i = 0;
	while(i < ph->philos)
	{
		if (ph->thread[i]->no_meals < ph->no_of_meals)
			return (1);
		i++;
	}
	return (0);
}