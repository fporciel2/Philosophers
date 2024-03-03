/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two_create_timers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:01:35 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/03 13:47:20 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* 'Philosophers' is a simulation of a solution to the dining philosophers
 * problem.
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
 * https://github.com/fporciel2/Philosophers
 *
 * This part of the program creates the two timers for the simulation with two
 * philosophers.
 */

#include "philo.h"

static int	philo_execute_two(int is_limited, t_gdata *global_data)
{
	pthread_t	odd;
	pthread_t	even;

	if (is_limited)
	{
		global_data->odd_philosophers[0].number_of_meals =
			global_data->number_of_times_each_philosopher_must_eat;
		global_data->even_philosophers[0].number_of_meals =
			global_data->number_of_times_each_philosopher_must_eat;
		pthread_create(&odd, NULL, philo_limit_two_odd_routine,
				(void *)&global_data->odd_philosophers[0]);
		pthread_create(&even, NULL, philo_limit_two_even_routine,
				(void *)&global_data->even_philosophers[0]);
		pthread_join(odd, NULL);
		pthread_join(even, NULL);
	}
	else
	{
		pthread_create(&odd, NULL, philo_two_odd_routine,
				(void *)&global_data->odd_philosophers[0]);
		pthread_create(&even, NULL, philo_two_even_routine,
				(void *)&global_data->even_philosophers[0]);
		pthread_join(odd, NULL);
		pthread_join(even, NULL);
	}
	return (philo_clean_global_data_two(global_data));
}

static void	philo_init_global_data_two_timers(t_gdata *global_data)
{
	global_data->odd_philosophers[0].id = 1;
	global_data->odd_philosophers[1].id = 0;
	global_data->even_philosophers[0].id = 2;
	global_data->even_philosophers[1].id = 0;
	global_data->forks[0].id = 1;
	global_data->forks[1].id = 2;
	global_data->forks[2].id = 0;
	global_data->timestamps[0].timestamp = 1;
	global_data->timestamps[1].timestamp = 2;
	global_data->timestamps[2].timestamp = 0;
	pthread_mutex_init(&global_data->timestamps[0].timestamp_mutex, NULL);
	pthread_mutex_init(&global_data->timestamps[1].timestamp_mutex, NULL);
	pthread_mutex_init(&global_data->forks[0].fork, NULL);
	pthread_mutex_init(&global_data->forks[1].fork, NULL);
	pthread_mutex_init(&global_data->mutexes->is_over_mutex, NULL);
	pthread_mutex_init(&global_data->mutexes->stdout_mutex, NULL);
	global_data->odd_philosophers[0].time_to_die = global_data->time_to_die;
	global_data->even_philosophers[0].time_to_die = global_data->time_to_die;
	global_data->odd_philosophers[0].time_to_eat = global_data->time_to_eat;
	global_data->even_philosophers[0].time_to_eat = global_data->time_to_eat;
}

static void	philo_assign_values_two_philosophers(t_gdata *global_data)
{
	global_data->odd_philosophers[0].time_to_sleep = global_data->time_to_sleep;
	global_data->even_philosophers[0].time_to_sleep =
		global_data->time_to_sleep;
	global_data->odd_philosophers[0].stdout_mutex =
		&global_data->mutexes->stdout_mutex;
	global_data->even_philosophers[0].stdout_mutex =
		&global_data->mutexes->stdout_mutex;
	global_data->odd_philosophers[0].is_over_mutex =
		&global_data->mutexes->is_over_mutex;
	global_data->even_philosophers[0].is_over_mutex =
		&global_data->mutexes->is_over_mutex;
	global_data->odd_philosophers[0].right_fork = &global_data->forks[0].fork;
	global_data->even_philosophers[0].right_fork = &global_data->forks[0].fork;
	global_data->odd_philosophers[0].left_fork = &global_data->forks[1].fork;
	global_data->even_philosophers[0].left_fork = &global_data->forks[1].fork;
	global_data->odd_philosophers[0].last_meal =
		&global_data->timestamps[0].timestamp;
	global_data->even_philosophers[0].last_meal =
		&global_data->timestamps[1].timestamp;
	global_data->odd_philosophers[0].is_over = &global_data->mutexes->is_over;
	global_data->even_philosophers[0].is_over = &global_data->mutexes->is_over;
}

int	philo_two_create_timers(int is_limited, t_gdata *global_data)
{
	global_data->odd_philosophers = (t_philo *)malloc(sizeof(t_philo) * 2);
	global_data->even_philosophers = (t_philo *)malloc(sizeof(t_philo) * 2);
	global_data->forks = (t_fork *)malloc(sizeof(t_fork) * 3);
	global_data->mutexes = (t_mutexes *)malloc(sizeof(t_mutexes));
	global_data->timestamps = (t_timestamp *)malloc(sizeof(t_timestamp) * 3);
	if (!global_data->odd_philosophers || !global_data->even_philosophers
		|| !global_data->forks || !global_data->mutexes
		|| !global_data->timestamps)
		return (philo_two_create_timers_error(global_data));
	philo_init_global_data_two_timers(global_data);
	philo_assign_values_two_philosophers(global_data);
	return (philo_execute_two(is_limited, global_data));
}
