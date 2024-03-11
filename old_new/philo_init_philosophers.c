/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_philosophers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:49:09 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/11 10:41:33 by fporciel         ###   ########.fr       */
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
 * This part of the program initializes the data structure of the
 * philosophers.
 */

#include "philo.h"

static void	philo_assign_last_forks(t_global *data, uint64_t i)
{
	if ((i + 1) == (data->number_of_philosophers - 2))
	{
		data->philosophers[i].forks_mutex = data->forks[i].fmutex;
		data->philosophers[i].right_fork = &data->forks[i].fork;
		data->philosophers[i].left_fork = &data->forks[i + 1].fork;
	}
	else if ((i + 1) == (data->number_of_philosophers - 1))
	{
		data->philosophers[i].forks_mutex = data->forks[i].fmutex;
		data->philosophers[i].right_fork = &data->forks[i - 1].fork;
		data->philosophers[i].left_fork = &data->forks[i].fork;
	}
	else
	{
		data->philosophers[i].forks_mutex = data->forks[i].fmutex;
		data->philosophers[i].right_fork = &data->forks[i].fork;
		data->philosophers[i].left_fork = &data->forks[i - 1].fork;
	}
}

static void	philo_assign_forks(t_global *data, uint64_t i)
{
	if ((!(data->number_of_philosophers % 2) && !(i % 2) && (i != 1))
		|| ((data->number_of_philosophers % 2) && !(i % 2) && (i != 1)
			&& ((i + 1) < (data->number_of_philosophers - 2))))
	{
		data->philosophers[i].forks_mutex = data->forks[i].fmutex;
		data->philosophers[i].right_fork = &data->forks[i].fork;
		data->philosophers[i].left_fork = &data->forks[i + 1].fork;
	}
	else if ((!(data->number_of_philosophers % 2) && ((i % 2) || (i == 1)))
		|| ((data->number_of_philosophers % 2) && ((i % 2) || (i == 1))
			&& ((i + 1) < (data->number_of_philosophers - 2))))
	{
		data->philosophers[i].forks_mutex = data->forks[i].fmutex;
		data->philosophers[i].right_fork = &data->forks[i - 1].fork;
		data->philosophers[i].left_fork = &data->forks[i].fork;
	}
	else if (((i + 1) >= (data->number_of_philosophers - 2))
		&& (data->number_of_philosophers % 2))
		philo_assign_last_forks(data, i);
	else
		return ;
}

static void	philo_assign_values(t_global *data, uint64_t i, t_input *input)
{
	data->philosophers[i].id = i + 1;
	data->philosophers[i].time_to_die = input->time_to_die;
	data->philosophers[i].time_to_eat = input->time_to_eat;
	data->philosophers[i].time_to_sleep = input->time_to_sleep;
	data->philosophers[i].number_of_meals = input->number_of_meals;
	data->philosophers[i].last_meal = &data->timestamps[i].timestamp;
	data->philosophers[i].intern_last_meal = data->timestamps[i].timestamp;
	data->philosophers[i].stdout_mutex = &data->mutexes->stdout_mutex;
	data->philosophers[i].start_mutex = &data->mutexes->start_mutex;
}

int	philo_init_philosophers(t_input *input, t_global *data)
{
	uint64_t	i;

	data->philosophers = (t_philo *)malloc(sizeof(t_philo)
			* (input->number_of_philosophers + 1));
	if (!data->philosophers)
		return (0);
	i = 0;
	while (i < input->number_of_philosophers)
	{
		philo_assign_values(data, i, input);
		philo_assign_forks(data, i);
		data->philosophers[i].timestamp = &data->timestamps[i].timestamp_mutex;
		data->philosophers[i].is_over_mutex = &data->mutexes->is_over_mutex;
		i++;
	}
	data->philosophers[i].id = 0;
	return (1);
}
/*
printf("%lu: ", (i + 1));
printf("right fork possessed: %p ", (void *)data->philosophers[i].right_fork);
printf("right fork assigned: %p ", (void *)&data->forks[i - 1].fork);
printf("left fork possessed: %p ", (void *)data->philosophers[i].left_fork);
printf("left fork assigned: %p\n", (void *)&data->forks[i].fork);
printf("\n\nfmutex possessed: %p ", (void *)data->philosophers[i].forks_mutex);
printf("fmutex assigned: %p\n\n", (void *)data->forks[i].fmutex);
 *
 */
