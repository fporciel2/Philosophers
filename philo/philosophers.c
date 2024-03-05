/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:53:45 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/05 13:44:50 by fporciel         ###   ########.fr       */
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
 * This part of the program gives the main codepath.
 */

#include "philo.h"

static void	philo_join_routines(t_gdata *data)
{
	uint64_t	i;

	i = 1;
	while (i <= data->number_of_philosophers)
	{
		pthread_join(data->threads[i - 1], NULL);
		i++;
	}
}

static void	philo_execute_routine(t_gdata *data, uint64_t *i)
{
	data->threads[*i] = data->philosophers[*i].philosopher;
	pthread_create(&data->philosophers[*i].philosopher, NULL,
			philo_routine, &data->philosophers[*i]);
	(*i)++;
}

static int	philo_normal_execution(t_gdata *data)
{
	uint64_t	i;

	i = 0;
	if ((data->number_of_philosophers % 2) == 0)
	{
		pthread_mutex_lock(&data->mutexes->is_over_mutex);
		while (data->philosophers[i].id != 0)
			philo_execute_routine(data, &i);
	}
	else
	{
		pthread_mutex_lock(&data->mutexes->is_over_mutex);
		while (data->philosophers[i].id != data->number_of_philosophers)
			philo_execute_routine(data, &i);
		data->threads[i] = data->philosophers[i].philosopher;
		pthread_create(&data->philosophers[i].philosopher, NULL,
				philo_last_routine, &data->philosophers[i]);
	}
	pthread_mutex_unlock(&data->mutexes->is_over_mutex);
	philo_join_routines(data);
	return (philo_cleanup(data));
}

static int	philo_initialize(t_input *input, t_gdata *global_data)
{
	global_data->threads = NULL;
	if (input->is_special)
		return (philo_special_execution(input, global_data));
	if (input->is_limited)
		philo_set_iterations(input->number_of_times_each_philosopher_must_eat,
			&global_data->number_of_meals);
	philo_init_global_data(input, global_data);
	if (!philo_init_timestamps(input, global_data)
		|| !philo_init_mutexes(input, global_data)
		|| !philo_init_forks(input, global_data)
		|| !philo_init_philosophers(input, global_data))
		return (philo_cleanup(global_data));
	global_data->threads = (pthread_t *)malloc(sizeof(pthread_t)
			* global_data->number_of_philosophers);
	if (global_data->threads == NULL)
		return (philo_cleanup(global_data));
	return (philo_normal_execution(global_data));
}

int	main(int argc, char **argv)
{
	t_input	input;
	t_gdata	global_data;

	argc--;
	argv++;
	if ((argc < 4) || (argc > 5))
		return (philo_input_is_not_valid(NULL));
	philo_init_input(&input);
	philo_number_of_philosophers(argv[0], &input);
	philo_init_time(argv[1], &input, 0);
	philo_init_time(argv[2], &input, 1);
	philo_init_time(argv[3], &input, 2);
	if (argc == 5)
		philo_number_of_times_each_philosopher_must_eat(argv[4], &input);
	if (!input.is_valid)
		return (philo_input_is_not_valid(&input));
	return (philo_initialize(&input, &global_data));
}
