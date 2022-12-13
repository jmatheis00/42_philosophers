/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:25:59 by jmatheis          #+#    #+#             */
/*   Updated: 2022/12/13 14:29:01 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*error_return(char *val, char *message)
{
	printf("%s\n", message);
	return (val);
}

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

void	prepare_exit(t_ph *ph, t_thread **thread)
{
	int	i;

	i = 0;
	while (i < ph->philos)
	{
		pthread_detach(thread[i]->id);
		pthread_mutex_destroy(&ph->forks[i]);
		i++;
	}
}
