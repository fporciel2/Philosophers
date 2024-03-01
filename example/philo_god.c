/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_god.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:59:54 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/01 10:45:42 by fporciel         ###   ########.fr       */
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
 * This function is a Leibnizian definer of pre-established harmony.
 */

#include "philo.h"

static int	philo_god_infinite_world(t_data *data)
{
	while (1)
	{
		if (!philo_start_meal(data)
			|| !philo_join_meal(data)
			|| !philo_join_sleep(data))
			return (philo_destroyer(data));
	}
	return (philo_destroyer(data));
}

static int	philo_god_finite_world(t_data *data)
{
	while (data->input->number_of_times_each_philosopher_must_eat--)
	{
		if (!philo_start_odd_meal(data)
			|| !philo_start_even_meal(data)
			|| !philo_join_odd_meal(data)
			|| !philo_start_odd_sleep(data)
			|| !philo_join_even_meal(data)
			|| !philo_join_sleep(data))
			return (philo_destroyer(data));
	}
	return (philo_destroyer(data));
}

static int	philo_god_solipsistic_world(t_data *data)
{
	usleep(data->input->time_to_die);
	return (philo_log(data->philosophers[0].id, DEAD, philo_get_time(),
			data->stdout_mutex));
}

int	philo_god(t_data *data)
{
	if (data->input->number_of_philosophers == 1)
		return (philo_god_solipsistic_world(data));
	else if (data->input->argc == 5)
		return (philo_god_finite_world(data));
	else
		return (philo_god_infinite_world(data));
}
