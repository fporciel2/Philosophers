/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:41:28 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/09 10:46:15 by fporciel         ###   ########.fr       */
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
 * This part of the program cleans up the global data.
 */

#include "philo.h"

static void	philo_destroy_forks(t_fork *forks, pthread_mutex_t *forks_mutex)
{
	uint64_t	i;
	uint64_t	j;

	i = 0;
	while (forks[i].id)
	{
		pthread_mutex_destroy(&forks[i].fork);
		i++;
	}
	j = forks[i].id / 2;
	i = 0;
	free(forks);
	while (i < j)
	{
		pthread_mutex_destroy(&forks_mutex[i]);
		i++;
	}
	free(forks_mutex);
}

static void	philo_destroy_timestamps(t_timestamp *timestamps)
{
	uint64_t	i;

	i = 0;
	while (timestamps[i].id)
	{
		pthread_mutex_destroy(&timestamps[i].timestamp_mutex);
		i++;
	}
	free(timestamps);
}

static void	philo_destroy_mutexes(t_mutex *mutexes)
{
	pthread_mutex_destroy(&mutexes->stdout_mutex);
	pthread_mutex_destroy(&mutexes->is_over_mutex);
	free(mutexes);
}

static int	philo_cleanup_null(t_gdata *data)
{
	data->philosophers = NULL;
	data->forks = NULL;
	data->timestamps = NULL;
	data->mutexes = NULL;
	data->fork = NULL;
	data->fmutex = NULL;
	return (0);
}

int	philo_cleanup(t_gdata *data)
{
	if (data->philosophers)
		free(data->philosophers);
	if (data->forks || data->fmutex)
		philo_destroy_forks(data->forks, data->fmutex);
	if (data->timestamps)
		philo_destroy_timestamps(data->timestamps);
	if (data->mutexes)
		philo_destroy_mutexes(data->mutexes);
	if (data->fork)
	{
		pthread_mutex_destroy(data->fork);
		free(data->fork);
	}
	if (data->threads)
		free(data->threads);
	return (philo_cleanup_null(data));
}
