/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_fmutexes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:35:20 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/10 12:42:30 by fporciel         ###   ########.fr       */
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
 * This part of the program initializes the mutexes of the mutexes of the forks.
 */

#include "philo.h"

static int	philo_send_fmutex_to_corresponding_forks(t_global *data)
{
	uint64_t	i;
	uint64_t	j;

	i = 0;
	j = 0;
	while (data->forks[i].id != 0)
	{
		data->forks[i].fmutex = &data->fmutex[j];
		i++;
		if (((i >= 2) && (i % 2 == 0))
			&& !(((data->number_of_philosophers % 2) != 0)
			&& ((i + 1) == data->number_of_philosophers)))
			j++;
	}
	return (1);
}

int	philo_init_fmutexes(t_input *input, t_global *data)
{
	uint64_t	i;

	i = 0;
	data->fmutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (input->number_of_philosophers / 2));
	if (!data->fmutex)
		return (0);
	while (i < (input->number_of_philosophers / 2))
	{
		pthread_mutex_init(&data->fmutex[i], NULL);
		i++;
	}
	return (philo_send_fmutex_to_corresponding_forks(data));
}
