/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:29:25 by jmatheis          #+#    #+#             */
/*   Updated: 2022/11/29 13:53:56 by jmatheis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>

void *computation(void *add)
{
	long sum = 0;
	long *add_num = (long *) (add);
	for (long i = 0; i < 1000000000; i++)
		sum += *add_num; 
	// printf("add: %ld\n", *add_num);
	return (NULL);
}

// void *computation()
// {
// 	printf("computation\n");
// 	return (NULL);
// }

int main()
{
	pthread_t thread1;
	pthread_t thread2;

	long value1 = 1;
	long value2 = 2;

	// computation( (void *) &value1);
	// computation( (void *) &value2);
	pthread_create(&thread1, NULL, computation, (void *) &value1);
	pthread_create(&thread2, NULL, computation, (void *) &value2);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	return (0);
}

