/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_study_mutex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:59:47 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/09 17:30:45 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* This file is part of the Philosophers project. It is meant to show an example
 * of usage of mutexes.
 * Copyright (C) 2024  Federico Porciello
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * For more information on how to contact me by electronic and paper mail
 * please see:
 * <your contact information here>
 */
/*
 * In this example we will try to count to 2.000.000 using a mutex. A mutex is a
 * mutual exclusive device that allows only one thread at a time to access a
 * resource. The first step is to include the headers needed by the functions
 * used in the program.
 */
#include <stdio.h>
#include <pthread.h>

/*
 * The second step is to define the variables that will be accessed by the
 * threads. It will be our common resource: a simple global variable.
 * The third step is to create the mutex that will protect the global variable.
 * I choose to declare a global mutex, because otherwise it would need other 
 * synchronization refinements, but it could typically be automatically defined
 * into a routine. 
 */
int				count = 0;
pthread_mutex_t	mutex;

/*
 * The fourth step is to define the routine that will be executed by the
 * threads. It will be  called by the 'pthread_create()' function. In this case,
 * the routine will increase the variable 'count' to 1.000.000 and then return
 * a NULL pointer. However, the instruction 'count++', that is a susceptible to
 * data races, is always executed after the 'pthread_mutex_lock()' instruction
 * and before the 'pthread_mutex_unlock()' instruction, which both hook the
 * global mutex. If the mutex is currently hooked by another thread, then the
 * execution of the routine stops until the other thread releases the mutex by
 * executing the 'pthread_mutex_unlock()' instruction.
 */
void	*routine(void *arg)
{
	int	i;

	i = -1;
	while (++i < 1000000)
	{
		pthread_mutex_lock(&mutex);
		count++;
		pthread_mutex_unlock(&mutex);
	}
	(void)arg;
	return (NULL);
}

/*
 * The fifth step is to create the threads and initialize the mutex.
 * The 'pthread_mutex_init()' function initializes the mutex. The first argument
 * is the mutex that will be initialized. The second argument is a pointer to 
 * the 'pthread_mutexattr_t' structure that will be used to initialize the
 * mutex (not used in this example).
 * The 'pthread_create()' function creates a new thread. The 'pthread_join()'
 * function waits for the thread to finish. The first argument is the thread
 * that will be created. The second argument is the routine to be executed by
 * the thread. The third argument is the argument that will be passed to the
 * routine, according to the POSIX standard.
 * Must be noted that the mutex is initialized and destroyed in the main
 * function: not destroying the mutex once used will cause a memory leak.
 */
int	main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread1, NULL, routine, NULL);
	pthread_create(&thread2, NULL, routine, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_mutex_destroy(&mutex);
	printf("Count: %d\n", count);
	return (0);
}
/*
 * The execution of this program will show the correct result: 2000000. 
 * The intended result is obtained because the read and write operations are
 * mutually excluded and cannot happen at the same unit of time.
 */
