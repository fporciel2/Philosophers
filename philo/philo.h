/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:48:31 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/16 16:01:25 by fporciel         ###   ########.fr       */
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
 * The following structure is needed by the 'philo_start_simulation' function
 * and by the threads to manage the data.
 */

typedef struct s_p
{
	uint64_t		*input;
	pthread_t		*timers;
	pthread_t		*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*table;
	uint64_t		i;
}					t_p;
/*
 * The following structure is needed by the 'philo_timer' routine in order to
 * pass the correct values to the philosophers.
 */

typedef struct s_t
{
	uint64_t		id;
	uint64_t		*start_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*table;
	int				*iseating;
	int				lonely;
	uint64_t		ttd;
	uint64_t		tte;
	uint64_t		tts;
	uint64_t		nte;
}
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
 */

void		philo_parse(int argc, char **argv, uint64_t *input);
int			philo_start_simulation(pthread_t *timers, uint64_t *input);
int			philo_log(uint64_t tmstmp, uint64_t id, char *status);
void		*philo_timer(void *p);
uint64_t	philo_get_time(void);

#endif
