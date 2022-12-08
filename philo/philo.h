/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:46:26 by jmatheis          #+#    #+#             */
/*   Updated: 2022/12/08 15:42:33 by jmatheis         ###   ########.fr       */
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

typedef struct s_thread
{
	pthread_t	id;

	int			left;
	int			right;

	int			no_meals;
	int			last_meal;
}		t_thread;

typedef struct s_ph
{
	int				iter;

	int				philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				no_of_meals;

	pthread_mutex_t	*forks;

	unsigned int	old_time;
	unsigned int	new_time;

	t_thread		**thread;
}				t_ph;

// INIT.C
t_ph		*init_ph(t_ph *ph, char **ag);
t_thread	**init_thread(t_ph *ph, t_thread **thread);

// ERROR_AND_FREE.C
char		*error_return(char *val, char *message);
void		free_structs(t_ph *ph, t_thread **thread);

int			check_arguments(int ac, char **ag);

int			timestamp(t_ph *ph);

// ROUTINE.C
void		take_forks(t_ph *ph);

void		sleeping(t_ph *ph);
void		eating(t_ph *ph);
void		thinking(t_ph *ph);
int			check_last_meal(t_ph *ph);

void		print_action(t_ph *ph, char *str);

#endif
