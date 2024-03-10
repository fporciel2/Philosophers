/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:23:18 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/10 15:36:39 by fporciel         ###   ########.fr       */
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
 * This part of the program contains the logging cycle.
 */

#include "philo.h"

static int	philo_escape_sequence(t_philo *philo, int param)
{
	if (param == 2)
		pthread_mutex_unlock(philo->start_mutex);
	pthread_mutex_unlock(philo->stdout_mutex);
	if (param == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->forks_mutex);
	}
	if (param == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->forks_mutex);
	}
	return (0);
}

int	philo_log(t_philo *philo, char *action, int param)
{
	if (param == 2)
		pthread_mutex_lock(philo->start_mutex);
	pthread_mutex_lock(philo->stdout_mutex);
	if (philo_timestamp() >= (philo->intern_last_meal + philo->time_to_die))
		return (philo_escape_sequence(philo, param));
	printf("[%lu] %lu %s\n", philo_timestamp(), philo->id, action);
	pthread_mutex_unlock(philo->stdout_mutex);
	return (1);
}
