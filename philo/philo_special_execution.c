/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_special_execution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:41:48 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/03 15:23:26 by fporciel         ###   ########.fr       */
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
 * This part of the program gives the special execution codepath, i.e. the code
 * that is executed in case the input has strange parameters. Strange cases:
 *
 * - The number of philosophers is 0.
 * - The number of times the simulation has to be executed is 0.
 * - The number of philosophers is 1.
 * - The number of philosophers is 2.
 * - The number of philosophers is 3.
 */

#include "philo.h"

static int	philo_one(t_input *input, t_gdata *global_data)
{
	pthread_t		philosopher;
	pthread_mutex_t	fork;

	pthread_mutex_init(&fork, NULL);
	global_data->forks = &fork;
	global_data->time_to_die = input->time_to_die;
	pthread_create(&philosopher, NULL, philo_one_routine, (void *)global_data);
	pthread_join(philosopher, NULL);
	pthread_mutex_destroy(&fork);
	return (0);
}

int	philo_special_execution(t_input *input, t_gdata *global_data)
{
	if ((input->number_of_philosophers == 0)
		|| ((input->is_limited)
			&& (input->number_of_times_each_philosopher_must_eat == 0)))
		return (1);
	else if (input->number_of_philosophers == 1)
		return (philo_one(input, global_data));
	else if (input->number_of_philosophers == 2)
		return (philo_two(input, global_data));/*
	else if (input->number_of_philosophers == 3)
		return (philo_three(input, global_data));*/
	return ((int)write(2, "WTF??!!!??\n", 11));
}
