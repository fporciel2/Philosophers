/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start_simulation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:29:02 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/29 11:51:07 by fporciel         ###   ########.fr       */
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
 * This part of the program starts the simulation by initializing the mutexes. 
 */

#include "philo.h"

static int	philo_init_mutexes(t_data *data)
{
	uint64_t	i;

	i = 0;
	pthread_mutex_init(&data->stdout_mutex, NULL);
	while (data->philosophers[i].id)
	{
		pthread_mutex_init(&data->forks[i].fork, NULL);
		pthread_mutex_init(&data->timestamps[i].timestamp, NULL);
		data->timestamps[i].last_meal = 0;
		i++;
	}
	return (philo_god(data));
}

int	philo_start_simulation(t_data *data)
{
	data->stdout_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!data->stdout_mutex)
		return (philo_cleaner(data));
	return (philo_init_mutexes(data));
}
