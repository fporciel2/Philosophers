/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:48:31 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/19 09:33:32 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* This is the header file for the Philosophers project.
 * Copyright (c) 2024 Federico Porciello
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
 * This is the header file for the Philosophers project. 
 * The ifndef block is an include guard that prevents multiple
 * inclusions of the same header file in the program: this prevents multiple
 * definitions of the same function or variable, which can lead to optimization
 * errors or undefined behaviors.
 * Another thing to define is the source to apply in order to extend the
 * standard to the POSIX 'pthread' library.
 */

#ifndef PHILO_H
# define PHILO_H
/*
 * Here are the included headers.
 *
 * TO MANAGE THE INPUT ARGUMENTS are used the stdint.h and the
 * stddef.h headers.
 * See the 'philo_input_check.c' file for more details.
 * TO USE POSIX EXTENTIONS (I.E. PTHREAD LIBRARY) is used, obviously, the
 * pthread.h header.
 */

# include <stdint.h>
# include <stddef.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <sys/types.h>
# include <sys/time.h>
/*
 * To properly use a correct number of threads, the macro MAXPHILO is defined at
 * compilation time. See the 'philo_input_check.c' file and the CC variable in
 * the Makefile for more details.
 * Here, we will establish a default value in case of errors.
 */

# ifndef MAXPHILO
#  define MAXPHILO 400
# endif
/*
 * The following definitions are the messages to display representing the
 * philosopher's status.
 */

# define THINKING "is thinking"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define FORK "has taken a fork"
# define DEAD "is dead"
/*
 * The 't_p' structure data type is used only for readability. It is meant to
 * share the resources with timers by the 'philo_start_simulation' function,
 * using a pointer to this structure type. Then, each timer will have its own
 * automatic variables taken from this structure, so that the access to a
 * resource done by the timer doesn't conflict with the access to other
 * resources pointed by this structure.
 */

typedef struct s_p
{
	pthread_mutex_t	*table;
	pthread_mutex_t	*forks;
	pthread_t		*philosophers;
	pthread_t		*timers;
	uint64_t		*input;
	uint64_t		i;
}					t_p;
/*
 * The 't_t' data type is used in part for readability and in part to share
 * informations between the timer and the philosopher. It takes values and
 * pointers using a logic similar to the 't_p' structure. However, in this case
 * the concept is to give to the philosopher a set of isolated variables to not
 * share with other philosophers or other threads, apart from specific
 * informations needed by the timer to kill the philosopher. I never thought
 * philosophy would be so deadly.
 * 'table' is used to lock the standard output.
 * 'left_fork' and 'right_fork' are used to lock the forks.
 * 'id' is the id of the philosopher.
 * 'start_time' is the timestamp at the start of the simulation and it is
 * updated at every meal.
 * 'ttd' is the time to die.
 * 'tte' is the time to eat.
 * 'tts' is the time to sleep.
 * 'iseating' is used by the timer to know if the philosopher is eating or not
 * and it is updated at every meal: set to 1 before logging the time to eat and
 * starting the meal, set to 0 at the end of the meal, before updating the
 * 'start_time' variable.
 * 'nte' is the number of times each philosopher must eat.
 * 'time' is the mutex used to lock 'start_time' and 'iseating' to communicate
 * with the timer.
 */

typedef struct s_t
{
	pthread_mutex_t	*table;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*time;
	uint64_t		id;
	uint64_t		*start_time;
	uint64_t		ttd;
	uint64_t		tte;
	uint64_t		tts;
	uint64_t		nte;
	int				*iseating;
	int				*end;
}					t_t;
/*
 * The 't_phi' data type is used for readability as a structure to store
 * informations used by the timer to analyze the correct order of time and
 * eating. This is done so that the philosopher can act without interferences in
 * its critical section while the timer is checking the order of time and
 * torturing the philosopher. See the 'philo_timer_clock' and 'philo_timer_init'
 * functions in the 'philo_timer.c' file for more details.
 */

typedef struct s_phi
{
	pthread_mutex_t	*table;
	pthread_mutex_t	*time;
	uint64_t		id;
	uint64_t		time_to_die;
	uint64_t		start_time;
	int				iseating;
	int				end;
}					t_phi;
/*
 * Here are the functions used in the program that need to be included using
 * this header.
 * 1.
 * The first function is 'philo_parse', from the 'philo_input_check.c' file: it
 * provides the parsing of the input arguments and their conversion into an
 * array of integers using the 'uint64_t' type.
 * 2.
 * The second function is 'philo_start_simulation', that initializes the threads
 * and the mutexes and starts the threads.
 * 3.
 * The third function is 'philo_log', that prints that displays the
 * philosopher's status.
 * 4.
 * The fourth function, 'philo_timer', is the routine executed by the threads
 * representing the timers.
 * 5.
 * The fifth function, 'get_time', is used to get the current timestamp in
 * milliseconds.
 * 6.
 * Finally, the 'philo_routine' function executes the philosopher's dinner.
 */

void		philo_parse(int argc, char **argv, uint64_t *input);
int			philo_start_simulation(pthread_t *timers, uint64_t *input);
int			philo_log(uint64_t tmstmp, uint64_t id, char *status);
void		*philo_timer(void *p);
uint64_t	philo_get_time(void);
void		*philo_routine(void *t);

#endif
