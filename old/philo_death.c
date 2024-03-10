/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:51:44 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/09 11:55:17 by fporciel         ###   ########.fr       */
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
 * This part of the program implements the death.
 * PARAM == 0 -----> pthread_mutex_unlock(p->forks_mutex) &&
 * pthread_mutex_unlock(p->timestamp).
 * PARAM == 1 -----> pthread_mutex_unlock(p->right_fork) &&
 * pthread_mutex_unlock(p->left_fork) && pthread_mutex_unlock(p->timestamp).
 * PARAM == 2 -----> like (param == 0) but without p->forks_mutex.
 */

#include "philo.h"

static void	philo_print_death(t_philo *p)
{
	if (philo_timestamp() > (*p->last_meal + p->time_to_die + 10))
	{
		pthread_mutex_unlock(p->stdout_mutex);
		return ;
	}
	printf("[%lu] %lu %s\n", philo_timestamp(), p->id, DEAD);
	while (p->number_of_philosophers--)
		usleep(p->time_to_die * 1000);
	pthread_mutex_unlock(p->stdout_mutex);
}

static void	philo_wait_for_death(t_philo *p)
{
	while (philo_timestamp() < (*p->last_meal + p->time_to_die))
		usleep(1000);
}

int	philo_death(t_philo *p, int param)
{
	pthread_mutex_lock(p->is_over_mutex);
	pthread_mutex_lock(p->stdout_mutex);
	pthread_mutex_unlock(p->timestamp);
	if (param == 0)
		pthread_mutex_unlock(p->forks_mutex);
	if (param == 1)
	{
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
	}
	philo_wait_for_death(p);
	philo_print_death(p);
	pthread_mutex_unlock(p->is_over_mutex);
	return (0);
}
