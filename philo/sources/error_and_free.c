/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:25:59 by jmatheis          #+#    #+#             */
/*   Updated: 2023/09/26 02:23:37 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_structs(t_ph *ph, t_thread **thread)
{
	int	i;

	i = 0;
	if (ph)
	{
		if (ph->forks)
			free (ph->forks);
		free (ph);
	}
	if (thread)
	{
		while (thread[i])
		{
			free(thread[i]);
			i++;
		}
		free (thread);
	}
}

// Detach: separates executed thread from thread object
void	prepare_exit(t_ph *ph, t_thread **thread)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&ph->print_mutex);
	while (i < ph->philos)
	{
		pthread_detach(thread[i]->id);
		pthread_mutex_destroy(&ph->forks[i]);
		i++;
	}
}
