/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_global_data.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:18:17 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/04 13:34:17 by fporciel         ###   ########.fr       */
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
 * This part of the program initializes the global data.
 */

#include "philo.h"

void	philo_init_global_data(t_input *input, t_gdata *data)
{
	data->number_of_philosophers = input->number_of_philosophers;
	data->time_to_die = input->time_to_die;
	data->time_to_eat = input->time_to_eat;
	data->time_to_sleep = input->time_to_sleep;
	data->number_of_meals = input->number_of_times_each_philosopher_must_eat;
	data->philosophers = NULL;
	data->forks = NULL;
	data->timestamps = NULL;
	data->is_over = 0;
	data->mutexes = NULL;
	data->fork = NULL;
}
