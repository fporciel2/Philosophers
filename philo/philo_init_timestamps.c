/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_timestamps.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:57:07 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/04 14:17:40 by fporciel         ###   ########.fr       */
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
 * This part of the program initializes the array of timestamps.
 */

#include "philo.h"

int	philo_init_timestamps(t_input *input, t_gdata *data)
{
	uint64_t	i;

	data->timestamps = (t_timestamp *)malloc(sizeof(t_timestamp)
			* (input->number_of_philosophers + 1));
	if (!data->timestamps)
		return (0);
	i = 0;
	while (i < input->number_of_philosophers)
	{
		data->timestamps[i].timestamp = 0;
		data->timestamps[i].id = i + 1;
		pthread_mutex_init(&data->timestamps[i].timestamp_mutex, NULL);
		i++;
	}
	data->timestamps[i].id = 0;
	i = 0;
	while (data->timestamps[i].id != 0)
	{
		printf("Value of timestamp: %lu\n", data->timestamps[i].timestamp);
		printf("Id of timestamp: %lu\n", data->timestamps[i].id);
		i++;
	}
	return (1);
}
