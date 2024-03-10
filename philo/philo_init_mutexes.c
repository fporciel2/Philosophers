/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_mutexes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:22:23 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/10 12:27:32 by fporciel         ###   ########.fr       */
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
 * This part of the program initializes the main mutexes shared between all the 
 * threads.
 */

#include "philo.h"

int	philo_init_mutexes(t_input *input, t_global *data)
{
	(void)input;
	data->mutexes = (t_mutex *)malloc(sizeof(t_mutex));
	if (!data->mutexes)
		return (0);
	pthread_mutex_init(&data->mutexes->stdout_mutex, NULL);
	pthread_mutex_init(&data->mutexes->start_mutex, NULL);
	pthread_mutex_init(&data->mutexes->is_over_mutex, NULL);
	return (1);
}
