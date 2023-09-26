/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 09:46:29 by jmatheis          #+#    #+#             */
/*   Updated: 2023/09/26 02:24:06 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// ./philo
// no_of_philos
// time_to_die
// time_to_eat
// time_to_sleep
// [no_of_times_each_philo_must_eat]

int	main(int ac, char **ag)
{
	t_ph		*ph;

	ph = NULL;
	if (check_arguments(ac, ag))
		return (1);
	ph = init_ph(ph, ag);
	if (!ph)
		return (-1);
	ph->thread = init_thread(ph, ph->thread);
	if (ph && ph->thread)
		start_routine(ph, ph->thread);
	prepare_exit(ph, ph->thread);
	free_structs(ph, ph->thread);
	return (0);
}

// system("leaks philo");