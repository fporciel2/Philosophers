/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 07:26:14 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/11 11:18:49 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 * 'Philosophers' is a simulation of a solution to the dining philosophers
 * problem.
 * Copyright (C) 2024 Federico Porciello
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
 * For more informations on how to contact me, please see
 * https://github.com/fporciel2/Philosophers
 *
 * This is the header file of the program.
 */

#ifndef PHILO_H
# define PHILO_H
# define _DEFAULT_SOURCE
# ifndef MAXPHILOS
#  define MAXPHILOS 200
# endif
# define THINK "is thinking"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define FORK "has taken a fork"
# define DEAD "died"
# define AINT64MAX "18446744073709551615"
# define NOINPUT "The input is not valid. Please, use the following format:\n"
# define EXECF "./philo"
# define NOPF "[number_of_philosophers]"
# define TTDF "[time_to_die]"
# define TTEF "[time_to_eat]"
# define TTSF "[time_to_sleep]"
# define NTEF "(optional)[number_of_times_each_philosopher_must_eat]"
# define BADNOP "insert a positive integer less than 18446744073709551615"
# define BADTHREADS "maximum: '(cat /proc/sys/kernel/threads-max) / 2'"
# define BADTTD "insert a positive integer less than 1000"
# define BADTTE "insert a positive integer less than 1000"
# define BADTTS "insert a positive integer less than 1000"
# define BADNOTEPME "insert a positive integer less than 18446744073709551615"
# include <time.h>
# include <sys/types.h>
# include <stdint.h>
# include <string.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_input
{
	uint64_t	number_of_philosophers;
	useconds_t	time_to_die;
	useconds_t	time_to_eat;
	useconds_t	time_to_sleep;
	uint64_t	number_of_meals;
	int			is_valid;
	int			is_limited;
	int			is_special;
	int			is_even;
	char		*badnop;
	char		*badthreads;
	char		*badttd;
	char		*badtte;
	char		*badtts;
	char		*badnotepme;
}				t_input;

typedef struct s_philo
{
	uint64_t		number_of_philosophers;
	uint64_t		id;
	useconds_t		time_to_die;
	useconds_t		time_to_eat;
	useconds_t		time_to_sleep;
	uint64_t		number_of_meals;
	uint64_t		*last_meal;
	uint64_t		intern_last_meal;
	pthread_mutex_t	*stdout_mutex;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	*timestamp;
	pthread_mutex_t	*is_over_mutex;
	pthread_mutex_t	*start_mutex;
	pthread_t		*timer;
}					t_philo;

typedef struct s_timer
{
	uint64_t		number_of_philosophers;
	uint64_t		id;
	useconds_t		time_to_die;
	useconds_t		time_to_eat;
	useconds_t		time_to_sleep;
	uint64_t		number_of_meals;
	uint64_t		*last_meal;
	pthread_mutex_t	*stdout_mutex;
	pthread_mutex_t	*timestamp;
	pthread_mutex_t	*is_over_mutex;
	pthread_mutex_t	*start_mutex;
	pthread_t		*philosopher;
}					t_timer;

typedef struct s_fork
{
	pthread_mutex_t	*fmutex;
	pthread_mutex_t	fork;
	uint64_t		id;
}					t_fork;

typedef struct s_timestamp
{
	uint64_t		timestamp;
	pthread_mutex_t	timestamp_mutex;
	uint64_t		id;
}					t_timestamp;

typedef struct s_mutex
{
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	is_over_mutex;
	pthread_mutex_t	stdout_mutex;
}					t_mutex;

typedef struct s_global
{
	uint64_t		number_of_philosophers;
	useconds_t		time_to_die;
	useconds_t		time_to_eat;
	useconds_t		time_to_sleep;
	uint64_t		number_of_meals;
	int				is_over;
	t_philo			*philosophers;
	t_timer			*timers;
	pthread_t		*thread_philosophers;
	pthread_t		*thread_timers;
	t_fork			*forks;
	t_timestamp		*timestamps;
	t_mutex			*mutexes;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*fmutex;
}					t_global;

/*Parsing functions.*/
void		philo_init_input(t_input *input);
void		philo_number_of_philosophers(char *argv, t_input *input);
void		philo_init_time(char *argv, t_input *input, int param);
void		philo_number_of_meals(char *argv, t_input *input);
int			philo_input_is_not_valid(t_input *input);
/*Initialization functions.*/
int			philo_special_execution(t_input *input, t_global *data);
void		philo_set_iterations(uint64_t number_of_meals, t_global *data);
void		philo_init_data(t_input *input, t_global *data);
int			philo_init_timestamps(t_input *input, t_global *data);
int			philo_init_mutexes(t_input *input, t_global *data);
int			philo_init_forks(t_input *input, t_global *data);
int			philo_init_fmutexes(t_input *input, t_global *data);
int			philo_init_philosophers(t_input *input, t_global *data);
int			philo_init_timers(t_input *input, t_global *data);
int			philo_cleanup(t_global *data);
/*Special execution functions.*/
void		*philo_special_routine(void *data);
uint64_t	philo_timestamp(void);
/*Normal execution functions.*/
void		*philo_routine(void *info);
void		*philo_timer(void *info);

#endif
