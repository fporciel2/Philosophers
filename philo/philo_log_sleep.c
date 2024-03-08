/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_log_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:20 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/08 14:56:51 by fporciel         ###   ########.fr       */
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
 * This part of the program logs the sleeping.
 */

#include "philo.h"

int	philo_log_sleep(t_philo *p)
{
	pthread_mutex_lock(p->timestamp);
	if (philo_timestamp() >= (*p->last_meal + (uint64_t)p->time_to_die))
		return (philo_death(p, 2));
	pthread_mutex_unlock(p->timestamp);
	pthread_mutex_lock(p->stdout_mutex);
	printf("[%lu] %lu %s\n", philo_timestamp(), p->id, SLEEP);
	pthread_mutex_unlock(p->stdout_mutex);
	return (1);
}
