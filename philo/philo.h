/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:46:26 by jmatheis          #+#    #+#             */
/*   Updated: 2022/12/05 21:59:15 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_ph
{
	int				philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				no_of_meals;

	pthread_mutex_t *forks;

	struct timeval	before;
	unsigned int	old_time;
	unsigned int	new_time;

}				t_ph;

typedef struct s_thread
{
	pthread_t id;

	int	left;
	int	right;

	int	no_meals;
	int	last_meal;
}		t_thread;

t_ph		*init_ph(t_ph *ph, char **ag);
// int		init_structs(t_ph *ph, char **ag, t_thread **thread);
t_thread	**init_thread(t_ph *ph, t_thread **thread);

int		check_arguments(int ac, char **ag);

int		timestamp();
void	print_action(t_ph *ph, int i, char *str);

#endif
