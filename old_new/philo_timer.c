/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_timer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:23:41 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/11 11:03:05 by fporciel         ###   ########.fr       */
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
 * This part of the program contains the timer functions.
 */

#include "philo.h"

static void	*philo_death(t_timer *timer)
{
	pthread_mutex_lock(timer->is_over_mutex);
	pthread_mutex_lock(timer->stdout_mutex);
	if (philo_timestamp() < (*timer->last_meal + timer->time_to_die + 10))
		printf("[%lu] %lu %s\n", philo_timestamp(), timer->id, DEAD);
	pthread_mutex_unlock(timer->timestamp);
	while (timer->number_of_philosophers--)
		usleep(timer->time_to_die * 1000);
	usleep(10000);
	pthread_mutex_unlock(timer->stdout_mutex);
	pthread_mutex_unlock(timer->is_over_mutex);
	return (NULL);
}

void	*philo_timer(void *info)
{
	t_timer	*timer;

	timer = (t_timer *)info;
	pthread_mutex_lock(timer->start_mutex);
	pthread_mutex_lock(timer->timestamp);
	*timer->last_meal = philo_timestamp();
	pthread_mutex_unlock(timer->timestamp);
	pthread_mutex_unlock(timer->start_mutex);
	while (1)
	{
		pthread_mutex_lock(timer->timestamp);
		if (philo_timestamp() >= (*timer->last_meal + timer->time_to_die))
			return (philo_death(timer));
		pthread_mutex_unlock(timer->timestamp);
	}
	return (NULL);
}
