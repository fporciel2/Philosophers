/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_study_datarace.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:01:46 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/09 15:56:08 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* This file is part of the Philosophers project. It is meant to show an example
 * of data race. Do not use it in your code.
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
 * https://github.com/fporciel2
 */
/*
 * A data race is a situation in which two or more threads try toaccess the 
 * same data at the same time. This can lead to an error in the final value of 
 * the data. To better understand the problem, you can see the following
 * example of a data race that leads to a race condition. In this situation, the
 * order in which the threads execute is important, because the threads will
 * access the same memory area and the same variable, but due to the race
 * condition the correct order may not be respected.
 * We want to count to 2.000.000. To do that with the multithreading we make two
 * threads that execute the same routine, and the routine increases the variable
 * count to 1.000.000, so that - in common sense - the final value of count is
 * 2.000.000 after the second thread has finished.
 *
 * The first step is to include the headers.
 */
#include <stdio.h>
#include <pthread.h>

/*
 * The second step is to define the variables that will be accessed by the
 * threads. It will be our common resource: a simple variable.
 */
int	count = 0;

/*
 * The third step is to define the routine that will be executed by the
 * threads. The routine will increase the variable count to 1.000.000 and then
 * return a void pointer.
 */
void	*routine(void *arg)
{
	int	i;

	i = -1;
	while (++i < 1000000)
		count++;
	(void)arg;
	return (NULL);
}

/*
 * The fourth step is to create the threads into the main function.
 * The second argument is the routine to be executed by the thread. The third
 * argument is the argument that will be passed to the routine, according to
 * the POSIX standard.
 */
int	main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;

	pthread_create(&thread1, NULL, routine, NULL);
	pthread_create(&thread2, NULL, routine, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("\nCount: %d\n", count);
	return (0);
}
/*
 * Executing the code above will result in unpredictable output and rarely to
 * the value 2000000: that's because the race condition caused by the data race
 * is not properly handled. 
 * A way to visualize this problem is to look at the assembli of the 'count++'
 * instruction.
 * To increase a variable by 1, at assembly level three operations are executed:
 *
 * ° 'read': read the value of the variable;
 * ° 'increase': increase the value of the variable;
 * ° 'write': update the value of the variable.
 *
 * The starting value of 'count' is 0. The assembly visualization of 'count++'
 * is:
 *
 * read: 0
 * increase: 0
 * write: 1
 *
 * The concurrent execution of the instruction should lead to something similar
 * to this visualization:
 *
 * | Thread 1    | Thread 2    |
 * | read: 0     | read: 1     |
 * | increase: 0 | increase: 1 |
 * | write: 1    | write: 2    |
 *
 * However, since the race condition is not properly handled, i.e. the threads
 * are not synchronized correctly, the scheduler can do something like this:
 *
 * | Thread 1    | Thread 2    |
 * | read: 0     | read: 0     |
 * | increase: 0 | increase: 0 |
 * | write: 1    | write: 1    |
 *
 * In that case, for example, the scheduler could have executed the operations
 * in this order: thread1-read, thread2-read, thread2-increase, thread2-write,
 * thread1-increase, thread1-write.
 * So, each thread could have executed the instruction 'count++' one time, for a
 * total of two instructions on the same global variable, but the value of the
 * variable is only increased once, because the 'read' instructions overlap.
 */
