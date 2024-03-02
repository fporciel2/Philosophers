/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:08:11 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/02 16:21:56 by fporciel         ###   ########.fr       */
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
 * This part of the program executes the routine for a single philosopher or
 * gets the current timestamp.
 */

#include "philo.h"

uint64_t	philo_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((uint64_t)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

void	*philo_one_routine(void *data)
{
	t_gdata	*gdata;

	gdata = (t_gdata *)data;
	usleep(gdata->time_to_die);
	printf("[%lu] 1 %s\n", philo_timestamp(), DEAD);
	return (NULL);
}
