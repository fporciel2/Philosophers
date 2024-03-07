/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_last_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:24:27 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/07 18:15:16 by fporciel         ###   ########.fr       */
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
 * This part of the program executes the lifecycle of the last philosopher if
 * the number of philosophers is odd.
 */

#include "philo.h"

void	philo_last_routine(t_philo *p)
{
	pthread_mutex_t	*tmp;

	tmp = p->right_fork;
	p->right_fork = p->third_fork;
	p->third_fork = tmp;
	pthread_mutex_lock(p->stdout_mutex);
	printf("%lu right fork %p - left fork %p\n", p->id, (void *)p->right_fork,
		(void *)p->left_fork);
	pthread_mutex_unlock(p->stdout_mutex);
}
