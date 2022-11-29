/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:29:25 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/29 14:52:27 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// void *routine()
// {
// 	printf("test from threads\n");
// 	sleep(3);
// 	printf("ending thread\n");
// 	return(NULL);
// }

// int main(int argc, char **argv)
// {
// 	pthread_t t1;
// 	pthread_t t2;
// 	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
// 	{
// 		printf("Error occured\n");
// 		return (1);
// 	}
// 	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
// 	{
// 		printf("Error occured\n");
// 		return (1);		
// 	}
// 	if (pthread_join(t1, NULL) != 0)
// 	{
// 		printf("Error occured\n");
// 		return (1);				
// 	}
// 	if (pthread_join(t2, NULL) != 0)
// 	{
// 		printf("Error occured\n");
// 		return (1);			
// 	}
// 	return (0);
// }

int mails = 0;
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
		i++;
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	pthread_t th[8];
	int	i;

	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < 8)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			printf("Error occured\n");
			return (1);
		}
		printf("Thread %d has started\n", i);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			printf("Error occured\n");
			return (1);				
		}
		printf("Thread %d has finished\n", i);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return (0);
}