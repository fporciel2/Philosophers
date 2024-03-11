/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_timer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:37:26 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/11 16:07:14 by fporciel         ###   ########.fr       */
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
 * This part of the program contains the timer's routine.
 */

#include "philo.h"

static void	*philo_death(t_timer *t)
{
	pthread_mutex_lock(t->stdout_mutex);
	if (philo_timestamp() < (*t->last_meal
			+ (t->time_to_die * t->number_of_philosophers)))
	{
		pthread_mutex_lock(t->is_over_mutex);
		printf("%lu %lu %s\n", philo_timestamp(), t->id, DEAD);
	}
	else
		pthread_mutex_lock(t->is_over_mutex);
	while (t->number_of_philosophers--)
		usleep(t->time_to_die * 1000);
	pthread_mutex_unlock(t->timestamp);
	pthread_mutex_unlock(t->stdout_mutex);
	pthread_mutex_unlock(t->is_over_mutex);
	return (NULL);
}

void	*philo_timer(void *info)
{
	t_timer	*t;

	t = (t_timer *)info;
	pthread_mutex_lock(t->start_mutex);
	pthread_mutex_unlock(t->start_mutex);
	pthread_mutex_lock(t->timestamp);
	*t->last_meal = philo_timestamp();
	pthread_mutex_unlock(t->timestamp);
	while (1)
	{
		pthread_mutex_lock(t->timestamp);
		if (*t->last_meal)
		{
			if (philo_timestamp() >= (*t->last_meal + t->time_to_die))
				return (philo_death(t));
		}
		else
		{
			*t->last_meal = philo_timestamp();
			usleep((t->time_to_die + 20) * 1000);
		}
		pthread_mutex_unlock(t->timestamp);
	}
	return (NULL);
}
