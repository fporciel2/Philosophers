/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_release_forks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 05:39:55 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/07 09:08:56 by fporciel         ###   ########.fr       */
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
 * This part of the program logs and executes the 'release forks' action.
 */

#include "philo.h"

static void	philo_wait_for_death(t_philo *p)
{
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
	while (philo_timestamp() < (*p->last_meal + p->time_to_die))
		usleep(1000);
}

static int	philo_handle_death_after_meal(t_philo *p)
{
	uint64_t	dying_time;

	pthread_mutex_lock(p->is_over_mutex);
	if (philo_timestamp() >= (*p->last_meal + (uint64_t)(p->time_to_die + 10)))
	{
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->timestamp);
		pthread_mutex_unlock(p->is_over_mutex);
		return (0);
	}
	philo_wait_for_death(p);
	pthread_mutex_lock(p->stdout_mutex);
	printf("[%lu] %lu %s\n", philo_timestamp(), p->id, DEAD);
	dying_time = p->number_of_philosophers;
	while (dying_time--)
		usleep(p->time_to_die * 1000);
	pthread_mutex_unlock(p->timestamp);
	pthread_mutex_unlock(p->stdout_mutex);
	pthread_mutex_unlock(p->is_over_mutex);
	return (0);
}

int	philo_release_forks(t_philo *p)
{
	pthread_mutex_lock(p->timestamp);
	if ((philo_timestamp() + p->time_to_sleep) >= (*p->last_meal
			+ p->time_to_die))
		return (philo_handle_death_after_meal(p));
	pthread_mutex_unlock(p->timestamp);
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
	return (1);
}
