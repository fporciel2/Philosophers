/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:26:21 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/04 11:53:11 by fporciel         ###   ########.fr       */
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
 * This part of the program implements the main routine using two philosophers.
 */

#include "philo.h"

static int	philo_two_routine_execution(t_gdata *global_data)
{
	if (!philo_will_eat(global_data, global_data->odd_philosophers))
		return (philo_kill_em_all(global_data, global_data->odd_philosophers));
	pthread_create(&global_data->odd_philosophers->philosopher,
			NULL, philo_odd_eat, global_data->odd_philosophers);
	pthread_join(global_data->even_philosophers->philosopher, NULL);
	if (!philo_will_eat(global_data, global_data->even_philosophers))
		return (philo_kill_em_all(global_data, global_data->even_philosophers));
	pthread_create(&global_data->even_philosophers->philosopher,
			NULL, philo_even_eat, global_data->even_philosophers);
	pthread_join(global_data->odd_philosophers->philosopher, NULL);
	if (!philo_will_sleep(global_data, global_data->odd_philosophers))
		return (philo_kill_em_all(global_data, global_data->odd_philosophers));
	pthread_create(&global_data->odd_philosophers->philosopher,
			NULL, philo_odd_sleep, global_data->odd_philosophers);
	pthread_join(global_data->even_philosophers->philosopher, NULL);
	if (!philo_will_sleep(global_data, global_data->even_philosophers))
		return (philo_kill_em_all(global_data, global_data->even_philosophers));
	pthread_create(&global_data->even_philosophers->philosopher,
			NULL, philo_even_sleep, global_data->even_philosophers);
	pthread_join(global_data->odd_philosophers->philosopher, NULL);
}

int	philo_two_routine(t_gdata *global_data)
{
	uint64_t	number_of_meals;

	number_of_meals = global_data->number_of_times_each_philosopher_must_eat;
	if (number_of_meals > 0)
	{
		while (number_of_meals--)
		{
			if (!philo_two_routine_execution(global_data))
				return (0);
		}
	}
	else
	{
		while (1)
		{
			if (!philo_two_routine_execution(global_data))
				return (0);
		}
	}
}
