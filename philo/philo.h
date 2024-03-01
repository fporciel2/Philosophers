/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:48:25 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/01 14:22:48 by fporciel         ###   ########.fr       */
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
# define BADNOP "insert a positive integer less than 18446744073709551615."
# define BADTHREADS "see 'cat /proc/sys/kernel/threads-max' for max threads."
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
	char		*badtts;
	char		*badnotepme;
}				t_input;

/* Parsing functions.*/
void	philo_init_input(t_input *input);
void	philo_number_of_philosophers(char *argv, t_input *input);
void	philo_init_time(char *argv, t_input *input);
void	philo_number_of_times_each_philosopher_must_eat(char *argv, t_input *i);
int		philo_input_is_not_valid(t_input *input);
/* Initialization functions. */
void	philo_init_global_data(t_gdata *global_data);
int		philo_init_philosophers(t_input *input, t_gdata *global_data);
int		philo_init_forks(t_gdata *global_data);
int		philo_init_mutexes(global_data);
int		philo_init_timestamps(t_gdata *global_data);
void	philo_globalize_times(t_input *input, t_gdata *global_data);
void	philo_set_iterations(t_input *input, t_gdata *global_data);
int		philo_special_execution(t_gdata *global_data);
/* Routine selection's functions.*/
int		philo_init_local(t_local *local, t_gdata *global_data);
void	philo_limited_even(pthread_t *odd, pthread_t *even, t_local *local);
void	philo_limited_odd(pthread_t *odd, pthread_t *even,
		pthread_t *last_three, t_local *local);
void	philo_unlimited_even(pthread_t *odd, pthread_t *even, t_local *local);
void	philo_unlimited_odd(pthread_t *odd, pthread_t *even,
		pthread_t *last_three, t_local *local);
int		philo_is_over(int is_over);

#endif
