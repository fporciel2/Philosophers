/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two_cleaners.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:53:42 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/03 14:01:14 by fporciel         ###   ########.fr       */
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
 * This part of the program cleans the memory for the code path with two
 * philosophers if and when is needed.
 */

#include "philo.h"

int	philo_clean_global_data_two(t_gdata *data)
{
	if (data->odd_philosophers)
		free(data->odd_philosophers);
	if (data->even_philosophers)
		free(data->even_philosophers);
	if (data->forks)
		free(data->forks);
	if (data->timestamps)
		free(data->timestamps);
	if (data->mutexes)
		free(data->mutexes);
	return (1);
}

int	philo_two_create_timers_error(t_gdata *global_data)
{
	if (global_data->odd_philosophers)
		free(global_data->odd_philosophers);
	if (global_data->even_philosophers)
		free(global_data->even_philosophers);
	if (global_data->forks)
		free(global_data->forks);
	if (global_data->timestamps)
		free(global_data->timestamps);
	if (global_data->mutexes)
		free(global_data->mutexes);
	return ((int)write(2, "'malloc' failed with two philosophers\n", 38));
}
