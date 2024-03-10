/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:04:24 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/10 17:02:27 by fporciel         ###   ########.fr       */
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
 * This part of the program cleans up the data.
 */

#include "philo.h"

static void	philo_destroy_forks(t_global *data)
{
	uint64_t	i;
	uint64_t	j;

	i = 0;
	while (data->forks[i].id)
	{
		pthread_mutex_destroy(&data->forks[i].fork);
		i++;
	}
	j = (i / 2);
	i = 0;
	free(data->forks);
	while (i < j)
	{
		pthread_mutex_destroy(&data->fmutex[i]);
		i++;
	}
	free(data->fmutex);
}

static void	philo_destroy_timestamps(t_global *data)
{
	uint64_t	i;

	i = 0;
	while (data->timestamps[i].id)
	{
		pthread_mutex_destroy(&data->timestamps[i].timestamp_mutex);
		i++;
	}
	free(data->timestamps);
}

static void	philo_destroy_mutexes(t_global *data)
{
	pthread_mutex_destroy(&data->mutexes->start_mutex);
	pthread_mutex_destroy(&data->mutexes->is_over_mutex);
	pthread_mutex_destroy(&data->mutexes->stdout_mutex);
	free(data->mutexes);
}

static int	philo_cleanup_null(t_global *data)
{
	data->number_of_philosophers = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->number_of_meals = 0;
	data->is_over = 1;
	data->philosophers = NULL;
	data->timers = NULL;
	data->thread_philosophers = NULL;
	data->thread_timers = NULL;
	data->forks = NULL;
	data->fmutex = NULL;
	data->timestamps = NULL;
	data->mutexes = NULL;
	data->fork = NULL;
	return (0);
}

int	philo_cleanup(t_global *data)
{
	if (data->philosophers)
		free(data->philosophers);
	if (data->timers)
		free(data->timers);
	if (data->forks || data->fmutex)
		philo_destroy_forks(data);
	if (data->timestamps)
		philo_destroy_timestamps(data);
	if (data->mutexes)
		philo_destroy_mutexes(data);
	if (data->fork)
	{
		pthread_mutex_destroy(data->fork);
		free(data->fork);
	}
	if (data->thread_philosophers)
		free(data->thread_philosophers);
	if (data->thread_timers)
		free(data->thread_timers);
	return (philo_cleanup_null(data));
}
