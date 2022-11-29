/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 09:46:29 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/29 11:36:24 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo
// no_of_philos
// time_to_die
// time_to_eat
// time_to_sleep
// [no_of_times_each_philo_must_eat]

int	main(int ac, char **ag)
{
	t_ph	*ph;

	ph = malloc(1 * sizeof(t_ph));
	if (!ph)
		return (1);
	memset(ph, 0, sizeof(t_ph));
	if (check_arguments(ac, ag) || init_struct(ph, ag))
		return (1);

	return (0);
}
