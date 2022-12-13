/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:46:26 by jmatheis          #+#    #+#             */
/*   Updated: 2022/12/13 15:57:54 by jmatheis         ###   ########.fr       */
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

	int			ph_id;
	int			left;
	int			right;

	int			no_meals;
	int			last_meal;

}		t_thread;

typedef struct s_ph
{
	int				iter;
	int				stop;

	int				philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				no_of_meals;

	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	pthread_t		death_thr;
	unsigned int	old_time;
	unsigned int	new_time;

	t_thread		**thread;
}				t_ph;

// PARSING_AND_INIT.C
int			check_arguments(int ac, char **ag);
t_ph		*init_ph(t_ph *ph, char **ag);
t_thread	**init_thread(t_ph *ph, t_thread **thread);

// ERROR_AND_FREE.C
char		*error_return(char *val, char *message);
void		free_structs(t_ph *ph, t_thread **thread);
void		prepare_exit(t_ph *ph, t_thread **thread);

// ROUTINE.C
void		start_routine(t_ph *ph, t_thread **thread);
void		print_action(t_ph *ph, t_thread *thread, char *str);

// CONTROL_THREAD.C
void		*deathcheck(void *arg);

// UTILS.C
void		get_starttime(t_ph *ph);
int			timestamp(t_ph *ph);
void		ft_usleep(long stop);
#endif
