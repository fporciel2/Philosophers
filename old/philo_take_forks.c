/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_take_forks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:41:22 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/09 12:51:07 by fporciel         ###   ########.fr       */
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
 * This part of the program implements the cycle to obtain the forks.
 */

#include "philo.h"

int	philo_take_forks(t_philo *p)
{
	pthread_mutex_lock(p->forks_mutex);
	pthread_mutex_lock(p->timestamp);
	if ((philo_timestamp() >= (*p->last_meal + (uint64_t)p->time_to_die))
		|| ((philo_timestamp() + (uint64_t)p->time_to_eat) >= (*p->last_meal
			+ (uint64_t)p->time_to_die)))
		return (philo_death(p, 0));
	pthread_mutex_lock(p->stdout_mutex);
	printf("First term: %lu\n", philo_timestamp() + p->time_to_eat);
	printf("Second term: %lu\n", *p->last_meal + p->time_to_eat);
	pthread_mutex_unlock(p->stdout_mutex);
	pthread_mutex_unlock(p->timestamp);
	pthread_mutex_lock(p->right_fork);
	pthread_mutex_lock(p->stdout_mutex);
	if (philo_timestamp() < (*p->last_meal + (uint64_t)p->time_to_die))
		printf("[%lu] %lu %s\n", philo_timestamp(), p->id, FORK);
	pthread_mutex_unlock(p->stdout_mutex);
	pthread_mutex_lock(p->left_fork);
	pthread_mutex_lock(p->stdout_mutex);
	if (philo_timestamp() < (*p->last_meal + (uint64_t)p->time_to_die))
		printf("[%lu] %lu %s\n", philo_timestamp(), p->id, FORK);
	pthread_mutex_unlock(p->stdout_mutex);
	pthread_mutex_unlock(p->forks_mutex);
	return (1);
}
