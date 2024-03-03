/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:48:25 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/03 15:27:01 by fporciel         ###   ########.fr       */
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
 * For more information on how to contact me by electronic and paper mail please
 * see:
 * https://github.com/fporciel2/Philosophers
 *
 * This is the header file of the entire program.
 */

#ifndef PHILO_H
# define PHILO_H
# define _DEFAULT_SOURCE
# ifndef MAXPHILOS
#  define MAXPHILOS 400
# endif
# define THINK "is thinking"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define FORK "has taken a fork"
# define DEAD "died"
# define AINT64MAX "18446744073709551615"
# define AINT64MAXLEN 20
# define NOINPUT "The input is not valid. Please, use the following format:\n"
# define EXECF "./philo "
# define NOPF "[number_of_philosophers] "
# define TTDF "[time_to_die] "
# define TTEF "[time_to_eat] "
# define TTSF "[time_to_sleep] "
# define NTEF "(optional)[number_of_times_each_philosopher_must_eat] \n"
# define BADNOP "insert a positive integer less than 18446744073709551615."
# define BADTHREADS "maximum: '(cat /proc/sys/kernel/threads-max) - 3'"
# define BADTTD "insert a positive integer less than 1000."
# define BADTTE "insert a positive integer less than 1000."
# define BADTTS "insert a positive integer less than 1000."
# define BADNOTEPME "insert a positive integer less than 18446744073709551615."
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
	uint64_t	number_of_times_each_philosopher_must_eat;
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
	pthread_t		philosopher;
	uint64_t		id;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		number_of_meals;
	uint64_t		*last_meal;
	int				*is_over;
	pthread_mutex_t	*stdout_mutex;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*timestamp;
	pthread_mutex_t	*is_over_mutex;
}					t_philo;

typedef struct s_fork
{
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
	pthread_mutex_t	is_over_mutex;
	pthread_mutex_t	stdout_mutex;
}					t_mutex;

typedef struct s_gdata
{
	uint64_t	number_of_philosophers;
	useconds_t	time_to_die;
	useconds_t	time_to_eat;
	useconds_t	time_to_sleep;
	uint64_t	number_of_times_each_philosopher_must_eat;
	int			is_over;
	t_philo		*odd_philosophers;
	t_philo		*even_philosophers;
	t_philo		*last_three_philosophers;
	t_philo		*philosophers;
	t_fork		*forks;
	t_mutex		*mutexes;
	t_timestamp	*timestamps;
}				t_gdata;

/* Parsing functions.*/
void		philo_init_input(t_input *input);
void		philo_number_of_philosophers(char *argv, t_input *input);
void		philo_init_time(char *argv, t_input *input, int param);
void		philo_number_of_times_each_philosopher_must_eat(char *argv,
				t_input *i);
int			philo_input_is_not_valid(t_input *input);
/* Initialization functions. */
int			philo_special_execution(t_input *input, t_gdata *global_data);
void		philo_set_iterations(uint64_t num, uint64_t *iterations);
void		philo_init_global_data(t_input *input, t_gdata *global_data);
int			philo_init_philosophers(t_input *input, t_gdata *global_data);
int			philo_init_mutexes(t_input *input, t_gdata *global_data);
int			philo_init_forks(t_input *input, t_gdata *global_data);
int			philo_init_timestamps(t_input *input, t_gdata *global_data);
int			philo_memory_error(t_gdata *global_data);
int			philo_memory_split_error(t_gdata *global_data);
void		philo_split_philosophers(t_gdata *global_data);
/* Routine selection's functions.*/
int			philo_init_local(t_local *local, t_gdata *global_data);
void		philo_limited_even(pthread_t *odd, pthread_t *even,
				t_local *local);
void		philo_limited_odd(pthread_t *odd, pthread_t *even,
				pthread_t *last_three, t_local *local);
void		philo_unlimited_even(pthread_t *odd, pthread_t *even,
				t_local *local);
void		philo_unlimited_odd(pthread_t *odd, pthread_t *even,
				pthread_t *last_three, t_local *local);
int			philo_is_over(int is_over);
/* philo_special_execution subroutines.*/
void		*philo_one_routine(void *data);
uint64_t	philo_timestamp(void);

#endif
