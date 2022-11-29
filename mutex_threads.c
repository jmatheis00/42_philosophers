/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_and_continue_threads.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:29:25 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/29 15:12:38 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	mails = 0;
int	lock = 0;
pthread_mutex_t mutex;

void *routine()
{
	int i;

	i = 0;
	while (i < 10000000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		// read mails
		// increment
		// write mails
		i++;
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	pthread_t p1, p2, p3, p4;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&p1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&p2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_create(&p3, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_create(&p4, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_join(p1, NULL) != 0)
		return (3);
	if (pthread_join(p2, NULL) != 0)
		return (4);
	if (pthread_join(p3, NULL) != 0)
		return (4);
	if (pthread_join(p4, NULL) != 0)
		return (4);
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return (0);
}