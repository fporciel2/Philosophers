/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start_meal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:22:43 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/29 11:36:20 by fporciel         ###   ########.fr       */
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
 * This part of the program starts the meal for each philosopher by operating a
 * mutually exclusive mutual exclusion.
 */

#include "philo.h"

static void	philo_assign_forks(t_data *data, t_info *info, uint64_t i)
{
	if ((info->id == data->input->number_of_philosophers)
		&& ((info->id % 2 != 0)))
	{
		info->right_fork = &data->forks[i - 2].fork;
		info->left_fork = &data->forks[i].fork;
	}
	else if ((info->id % 2) != 0)
	{
		info->right_fork = &data->forks[i].fork;
		info->left_fork = &data->forks[i + 1].fork;
	}
	else
	{
		info->right_fork = &data->forks[i - 1].fork;
		info->left_fork = &data->forks[i].fork;
	}
}

static void	philo_assign_resources_coordinates(t_data *data, t_info *info,
		uint64_t i)
{
	info->stdout_mutex = data->stdout_mutex;
	info->time_to_die = data->input->time_to_die;
	info->time_to_eat = data->input->time_to_eat;
	info->time_to_sleep = data->input->time_to_sleep;
	info->id = data->philosophers[i].id;
	info->last_meal = data->timestamps[i].last_meal;
	info->timestamp = &data->timestamps[i].timestamp;
}

int	philo_start_meal(t_data *data)
{
	uint64_t	i;
	t_info		info;

	i = 0;
	while (data->philosophers[i].id)
	{
		philo_assign_resources_coordinates(data, &info, i);
		philo_assign_forks(data, &info, i);
		pthread_create(&data->philosophers[i].philosopher, NULL,
			philo_meal_routine, (void *)&info);
		i++;
	}
	return (1);
}
