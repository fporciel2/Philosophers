/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_timers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:42:58 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/10 13:57:29 by fporciel         ###   ########.fr       */
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
 * This part of the program initializes the timers.
 */

#include "philo.h"

static void	philo_assign_values(t_global *data, uint64_t i, t_input *input)
{
	data->timers[i].id = i + 1;
	data->timers[i].time_to_die = input->time_to_die;
	data->timers[i].time_to_eat = input->time_to_eat;
	data->timers[i].time_to_sleep = input->time_to_sleep;
	data->timers[i].number_of_meals = input->number_of_meals;
	data->timers[i].last_meal = &data->timestamps[i].timestamp;
	data->timers[i].intern_last_meal = data->timestamps[i].timestamp;
	data->timers[i].stdout_mutex = &data->mutexes->stdout_mutex;
	data->timers[i].start_mutex = &data->mutexes->start_mutex;
}

int	philo_init_timers(t_input *input, t_global *data)
{
	uint64_t	i;

	data->timers = (t_timer *)malloc(sizeof(t_timer)
			* (input->number_of_philosophers + 1));
	if (!data->timers)
		return (0);
	i = 0;
	while (i < input->number_of_philosophers)
	{
		philo_assign_values(data, i, input);
		data->timers[i].timestamp = &data->timestamp[i].timestamp_mutex;
		data->timers[i].is_over_mutex = &data->mutexes->is_over_mutex;
		i++;
	}
	data->timers[i].id = 0;
	return (1);
}
