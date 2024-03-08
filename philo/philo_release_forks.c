/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_release_forks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:18:24 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/08 14:35:30 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* 'Philosophers'is a simulation of a solution to the dining philosophers
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
 * This part of the program handles the releasing of the forks.
 */

#include "philo.h"

int	philo_release_forks(t_philo *p)
{
	pthread_mutex_lock(p->timestamp);
	if (((philo_timestamp() + (uint64_t)p->time_to_sleep)
		>= (*p->last_meal + (uint64_t)p->time_to_die))
		|| ((philo_timestamp() + (uint64_t)p->time_to_eat)
			>= (*p->last_meal + (uint64_t)p->time_to_die)))
		return (philo_death(p, 1));
	pthread_mutex_unlock(p->timestamp);
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
	return (1);
}
