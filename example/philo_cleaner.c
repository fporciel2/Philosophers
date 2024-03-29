/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:40:10 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/28 15:16:43 by fporciel         ###   ########.fr       */
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
 * This is a little cleaner.
 */

#include "philo.h"

int	philo_cleaner(t_data *data)
{
	if (data->philosophers)
		free(data->philosophers);
	if (data->forks)
		free(data->forks);
	if (data->timestamps)
		free(data->timestamps);
	if (data->stdout_mutex)
		free(data->stdout_mutex);
	return (0);
}

int	philo_destroyer(t_data *data)
{
	uint64_t	i;

	i = 0;
	pthread_mutex_destroy(&data->stdout_mutex);
	while (data->philosophers[i].id)
	{
		pthread_mutex_destroy(&data->forks[i].fork);
		pthread_mutex_destroy(&data->timestamps[i].timestamp);
		i++;
	}
	return (philo_cleaner(data));
}
