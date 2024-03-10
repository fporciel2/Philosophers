/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 09:10:05 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/10 17:03:24 by fporciel         ###   ########.fr       */
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
 * This part of the program contains the main function.
 */

#include "philo.h"

static void	philo_join_routines(t_global *data)
{
	uint64_t	i;

	i = 0;
	while (i != data->number_of_philosophers)
	{
		pthread_join(data->thread_philosophers[i], NULL);
		pthread_join(data->thread_timers[i], NULL);
		i++;
	}
}

static void	philo_execute_routine(t_global *data, uint64_t *i)
{
	pthread_create(&data->thread_philosophers[*i], NULL,
			philo_routine, (void *)&data->philosophers[*i]);
	pthread_create(&data->thread_timers[*i], NULL,
			philo_timer, (void *)&data->timers[*i]);
	(*i)++;
}

static int	philo_normal_execution(t_global *data)
{
	uint64_t	i;

	i = 0;
	pthread_mutex_lock(&data->mutexes->start_mutex);
	while (data->philosophers[i].id)
		philo_execute_routine(data, &i);
	pthread_mutex_unlock(&data->mutexes->start_mutex);
	philo_join_routines(data);
	return (philo_cleanup(data));
}

static int	philo_initialize(t_input *input, t_global *data)
{
	data->thread_philosophers = NULL;
	data->thread_timers = NULL;
	if (input->is_special)
		return (philo_special_execution(input, data));
	if (input->is_limited)
		philo_set_iterations(input->number_of_meals, data);
	philo_init_data(input, data);
	if (!philo_init_timestamps(input, data)
		|| !philo_init_mutexes(input, data)
		|| !philo_init_forks(input, data)
		|| !philo_init_fmutexes(input, data)
		|| !philo_init_philosophers(input, data)
		|| !philo_init_timers(input, data))
		return (philo_cleanup(data));
	data->thread_philosophers = (pthread_t *)malloc(sizeof(pthread_t)
			* input->number_of_philosophers);
	data->thread_timers = (pthread_t *)malloc(sizeof(pthread_t)
			* input->number_of_philosophers);
	if (!data->thread_philosophers || !data->thread_timers)
		return (philo_cleanup(data));
	return (philo_normal_execution(data));
}

int	main(int argc, char **argv)
{
	t_input		input;
	t_global	data;

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
		philo_number_of_meals(argv[4], &input);
	if (!input.is_valid)
		return (philo_input_is_not_valid(&input));
	return (philo_initialize(&input, &data));
}
