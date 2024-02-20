/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:22:16 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/20 16:20:52 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 * 'Philosophers' is a simulation that implements a solution to the dining
 * philosophers problem in C. This version is not ready to use and it is not
 * safe to use. 
 * This is the header file.
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
 * https://github.com/fporciel2/Philosophers
 *
 * PHILOSOPHERS
 *
 * This is the header file. It contains the prototypes for the functions that
 * are used in the simulation.
 * The header is included across multiple C files and so it implements an ifndef
 * block as an include guard to prevent multiple definitions of the functions.
 * It also prevents the headers from being included multiple times. Indeed,
 * there are many headers included in this file, for different purposes.
 * In this header are also defined some constants and structures.
 */
// Include guards is provided using "ifndef block". PHILO_H is defined by the
// preprocessor when the header is included for the first time, but not again,
// so that multiple inclusions do not cause multiple definitions. The ifndef
// block starts with #ifndef and ends with #endif.
#ifndef PHILO_H
// The name PHILO_H is used to make the include guard effective.
# define PHILO_H
// Since the program applies the C17 standard and uses the 'usleep' function, it
// requires the retrocompatibility of the 'unistd.h' header, performed by
// defining the _DEFAULT_SOURCE macro.
# define _DEFAULT_SOURCE
/* INCLUDED HEADERS */
// Since this version of the program is experimental and demonstration and uses
// deprecated functions and does not handle complex classes of errors, in
// particular those resulting from a failure of the functions from the POSIX
// threading extension, and since the 'usleep' function, used to pause threads,
// does not accept values higher than the maximum allowed by the 'useconds_t'
// type, execution values higher than 1000000 are not accepted: the privileged
// type for the second, third and fourth input value will therefore be
// 'useconds_t', which requires the inclusion of 'time.h' and 'sys/types.h'.
# include <time.h>
# include <sys/types.h>
// However, since the value of the first parameter received by the program is
// bound to a maximum thread limit that varies depending on what is written
// inside '/proc/sys/kernel/threads-max', the 'uint64_t' type is used to handle
// all cases. Since, on the other hand, within the program a number of threads
// equal to the double the number of philosophers is used, even if the maximum
// allowed number of threads is equal to or greater than the maximum value
// allowed for 'uint64_t', this maximum value will be used as a reference point
// to indicate invalid input of the form '(uint64_t)-1'. This mechanism requires
// the use of 'stdint.h' and will also be adopted for the possible fifth input
// parameter, more or less without any reason other than the fact that this
// version of the program is not ready to use.
# include <stdint.h>
// In order to transfer variables and structures beyond the scopes of individual
// functions, some parts of the code require their memory areas to be
// initialized with fixed values that will not be used in subsequent steps. To
// do this, the code uses the 'memset' function, which requires the inclusion of
// 'string.h', and the handling of the 'size_t' type, which requires the
// inclusion of 'stddef.h'.
# include <string.h>
# include <stddef.h>
# include <stddef.h>
// In order to record the state of a philosopher at a given timestamp the
// 'printf' function is used, which requires including 'stdio.h'.
# include <stdio.h>
// In order to allocate an exact amount of memory to match the inputs, the heap
// will be used to register the threads and mutexes: this requires the use of
// the 'malloc' and 'free' functions, which in turn require the inclusion of
// 'stdlib.h'.
# include <stdlib.h>
// The 'write' function, which requires the inclusion of 'unistd.h', is
// primarily used to send error descriptions of the input to the standard error
// stream. The same header is used by the 'usleep' function, which is used to
// stop threads for an amount of time defined by the 'time_to_eat' and
// 'time_to_sleep' parameters, but also, in the case of timers, by
// 'time_to_die'.
# include <unistd.h>
// Finally, both to record the current timestamp in the standard output stream
// corresponding to the state change in a philosopher, and to compare the
// current timestamp with the one corresponding to the start of the dinner or
// the end of the last meal of each philosopher, the program repeats to the
// 'gettimeofday' function, which requires the inclusion of 'sys/time.h'.
# include <sys/time.h>
// The threads and mutexes in the program are managed thanks to functions
// defined within 'pthread.h', which is therefore included in the program
// header. The functions selected for this purpose are 'pthread_create',
// 'pthread_detach', 'pthread_join', 'pthread_mutex_init', 'pthread_mutex_lock',
// 'pthread_mutex_unlock', 'pthread_mutex_destroy'.
# include <pthread.h>
// The maximum thread limit is retrieved from the Makefile to define the maximum
// number of philosophers at compile time. If MAXTHREADS is equal to the maximum
// number of threads that can be opened by a process and MAXPHILOS the maximum
// number of threads that can execute the philosopher's routine in the
// simulation, MAXPHILOS (which is the name that is used by the constant) is
// equal to MAXTHREADS / 2. 
// However, it is possible that the compilation rule present in the Makefile is
// not used to test the program, or that the definition simply fails. To prevent
// this problem, an ifndef block is used here that defines the macro in that
// case by a value that is acceptable for a basic test.
# ifndef MAXPHILOS
#  define MAXPHILOS 400
# endif
/* Below, the strings that apply to the standard output to signify the different
 * states that can be assumed by a thread symbolizing a philosopher are defined
 * as constants. */
// 'THINK' indicates the phase between suspending the thread or starting it and
// the start of the resource race condition. It symbolizes on the one hand the
// thinker's expectation as meditation, on the other the confounding variable
// that eliminates the deterministic limit entrusted to the concurrent
// development of the process.
# define THINK "is thinking"
// 'FORK' indicates exclusive possession of a resource, defined as a fork. In
// reality, rather than signifying it, it symbolizes it, since in this program
// the resources defined as forks are not actually allocated: what is recorded
// is actually a phase in which the process could have exclusive access to
// resources that are mutually requested by processes competitors, if these were
// physically produced.
# define FORK "has taken a fork"
// 'EAT' indicates the actual carrying out of the process through the resources
// previously acquired and secured, i.e. through the resources to which the
// process has exclusive access and which are mutually shared with other
// processes in phases different from that in which the process has exclusive
// possession of them: in the specific case of this program, the process simply
// remains suspended during this phase, but during the suspension a resource,
// not mutually shared with the processes to which the philosopher's routine is
// applied, but shared with the timer, cheanges its state, and changes it again
// at the end of it.
# define EAT "is eating"
// 'SLEEP' represents a possible delay between 'EAT' and 'THINK', during which
// the process has no resources and does not compete for any resources.
# define SLEEP "is sleeping"

/*The types needed to transmit values and resources to the different processes
 * are defined below. */
// The first type, 't_input', is designed to record the parameters that the
// program receives as input. The first parameter that the program receives as
// input is 'nop', the number of philosophers, i.e. the number of threads to
// which the user asks to entrust the philosopher's routine: this value cannot
// exceed the maximum value that can be assigned to a variable of type
// 'uint64_t', and causes an error in the simulation if it exceeds the value of
// the expression (MAXPHILOS - 1), where the maximum number of philosophers is
// subtracted by a deviation value which will later be used to facilitate a
// count. 
