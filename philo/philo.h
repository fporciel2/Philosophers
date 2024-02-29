/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:14:06 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/29 11:36:51 by fporciel         ###   ########.fr       */
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
 * This is the header file.
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

typedef struct s_philo
{
	uint64_t	id;
	pthread_t	philosopher;
}				t_philo;

typedef struct s_fork
{
	uint64_t		id;
	pthread_mutex_t	fork;
}					t_fork;

typedef struct s_tmstmp
{
	uint64_t		id;
	uint64_t		last_meal;
	pthread_mutex_t	timestamp;
}					t_tmstmp;

typedef struct s_input
{
	uint64_t	number_of_philosophers;
	useconds_t	time_to_die;
	useconds_t	time_to_eat;
	useconds_t	time_to_sleep;
	uint64_t	number_of_times_each_philosopher_must_eat;
	int			argc;
}				t_input;

typedef struct s_data
{
	struct s_philo	*philosophers;
	struct s_fork	*forks;
	struct s_tmstmp	*timestamps;
	struct s_input	*input;
	pthread_mutex_t	*stdout_mutex;
}					t_data;

typedef struct s_info
{
	pthread_mutex_t	*stdout_mutex;
	useconds_t		time_to_die;
	useconds_t		time_to_eat;
	useconds_t		time_to_sleep;
	uint64_t		id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	uint64_t		*last_meal;
	pthread_mutex_t	*timestamp;
}					t_info;

int			philo_take_numbers(t_input *input, char **argv, int argc);
int			philo_take_times(t_input *input, char **argv);
uint64_t	philo_atolui(char *str);
int			philo_init(t_input *input);
int			philo_start_simulation(t_data *data);
int			philo_cleaner(t_data *data);
int			philo_destroyer(t_data *data);
int			philo_god(t_data *data);
uint64_t	philo_get_time(void);
uint64_t	philo_log(uint64_t id, char *str, uint64_t timestamp,
				pthread_mutex_t *stdout_mutex);
int			philo_start_meal(t_data *data);
int			philo_join_meal(t_data *data);
int			philo_start_sleep(t_data *data);
int			philo_join_sleep(t_data *data);
void		*philo_meal_routine(void *info);

#endif
