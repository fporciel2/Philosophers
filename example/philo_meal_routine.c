/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_meal_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:17:26 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/01 10:38:48 by fporciel         ###   ########.fr       */
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
 * This part of the program is the meal routine.
 */

#include "philo.h"

void	philo_eat(t_info *info)
{
	philo_log(info->id, EAT, philo_get_time(), info->stdout_mutex);
	usleep(info->time_to_eat);
	pthread_mutex_lock(info->timestamp);
	*info->timestamp->last_meal = philo_get_time();
	pthread_mutex_unlock(info->right_fork);
	pthread_mutex_unlock(info->left_fork);
	pthread_mutex_unlock(info->timestamp);
}

void	philo_take_forks(t_info *info)
{
	pthread_mutex_lock(info->right_fork);
	philo_log(info->id, FORK, philo_get_time(), info->stdout_mutex);
	pthread_mutex_lock(info->left_fork);
	philo_log(info->id, FORK, philo_get_time(), info->stdout_mutex);
}

void	*philo_meal_routine(void *info)
{
	t_info	*info_copy;

	info_copy = (t_info *)info;
	pthread_mutex_lock(info_copy->timestamp);
	if (*info_copy->timestamp->last_meal == 0)
		*info_copy->timestamp->last_meal = philo_get_time();
	pthread_mutex_unlock(info_copy->timestamp);
	philo_take_forks(info_copy);
	if (philo_check_death_before_right_fork(info_copy))
		return (NULL);
	philo_take_forks(info_copy);
	if (philo_check_death_before_eat(info_copy))
		return (NULL);
	philo_eat(info_copy);
}
