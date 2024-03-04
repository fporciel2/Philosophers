/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:08:11 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/04 10:21:56 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* 'Philosophers' is a simulation of a solution to the dining philosophers
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
 * For more information on how to contact me by electronic and paper mail
 * please see:
 * https://github.com/fporciel2/Philosophers
 *
 * This part of the program initializes the data for the strange case with two
 * philosophers.
 */

#include "philo.h"

void	philo_init_two_global_data(t_gdata *data, t_input *input)
{
	data->number_of_philosophers = input->number_of_philosophers;
	data->time_to_die = input->time_to_die;
	data->time_to_eat = input->time_to_eat;
	data->time_to_sleep = input->time_to_sleep;
	data->number_of_times_each_philosopher_must_eat =
		input->number_of_times_each_philosopher_must_eat;
}

void	philo_init_two_forks(t_gdata *data, t_fork *forks)
{
	data->forks = forks;
	data->forks[0].id = 1;
	data->forks[1].id = 2;
	data->forks[2].id = 0;
	pthread_mutex_init(&data->forks[0].fork, NULL);
	pthread_mutex_init(&data->forks[1].fork, NULL);
}

void	philo_init_two_timestamps(t_gdata *data, t_timestamp *timestamps)
{
	data->timestamps = timestamps;
	data->timestamps[0].id = 1;
	data->timestamps[1].id = 2;
	data->timestamps[2].id = 0;
	pthread_mutex_init(&data->timestamps[0].timestamp_mutex, NULL);
	pthread_mutex_init(&data->timestamps[1].timestamp_mutex, NULL);
}

void	philo_init_two_mutexes(t_gdata *data, t_mutex *mutexes)
{
	data->mutexes = mutexes;
	pthread_mutex_init(&data->mutexes->is_over_mutex, NULL);
	pthread_mutex_init(&data->mutexes->stdout_mutex, NULL);
}

void	philo_init_two_philosophers(t_gdata *data, t_philo *philosophers)
{
	philosophers[0].id = 1;
	philosophers[1].id = 2;
	philosophers[2].id = 0;
	data->odd_philosophers = &philosophers[0];
	data->even_philosophers = &philosophers[1];
	data->odd_philosophers->time_to_die = data->time_to_die;
	data->even_philosophers->time_to_die = data->time_to_die;
	data->odd_philosophers->time_to_eat = data->time_to_eat;
	data->even_philosophers->time_to_eat = data->time_to_eat;
	data->odd_philosophers->time_to_sleep = data->time_to_sleep;
	data->even_philosophers->time_to_sleep = data->time_to_sleep;
	data->odd_philosophers->number_of_meals =
		data->number_of_times_each_philosopher_must_eat;
	data->even_philosophers->number_of_meals =
		data->number_of_times_each_philosopher_must_eat;
	data->odd_philosophers->last_meal = &data->timestamps[0].timestamp;
	data->even_philosophers->last_meal = &data->timestamps[1].timestamp;
	data->odd_philosophers->is_over = &data->mutexes->is_over;
	data->even_philosophers->is_over = &data->mutexes->is_over;
	data->odd_philosophers->stdout_mutex = &data->mutexes->stdout_mutex;
	data->even_philosophers->stdout_mutex = &data->mutexes->stdout_mutex;
}
