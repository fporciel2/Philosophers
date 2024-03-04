/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:53:45 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/04 13:40:32 by fporciel         ###   ########.fr       */
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

static int	philo_initialize(t_input *input, t_gdata *global_data)
{
	if (input->is_special)
		return (philo_special_execution(input, global_data));
	if (input->is_limited)
		philo_set_iterations(input->number_of_times_each_philosopher_must_eat,
			&global_data->number_of_meals);
	philo_init_global_data(input, global_data);
	if (!philo_init_timestamps(input, global_data))
		return (0);
	printf("Initialized global data\n");
	printf("number_of_philosophers: %lu\n",
			global_data->number_of_philosophers);
	printf("time_to_die: %u\n", global_data->time_to_die);
	printf("time_to_eat: %u\n", global_data->time_to_eat);
	printf("time_to_sleep: %u\n", global_data->time_to_sleep);
	printf("number_of_times_each_philosopher_must_eat: %lu\n",
		global_data->number_of_meals);
	printf("is_over: %d\n", global_data->is_over);
	printf("is_limited: %d\n", input->is_limited);
	printf("is_valid: %d\n", input->is_valid);
	printf("timestamp: %lu\n", philo_timestamp());
	printf("mutexes: %p\n", (void *)global_data->mutexes);
	printf("forks: %p\n", (void *)global_data->forks);
	printf("philosophers: %p\n", (void *)global_data->philosophers);
	printf("timestamps: %p\n", (void *)global_data->timestamps);
	return (philo_cleanup(global_data));
}/*
	if (!philo_init_timestamps(input, global_data)
		|| !philo_init_mutexes(input, global_data)
		|| !philo_init_forks(input, global_data)
		|| !philo_init_philosophers(input, global_data))
		return (philo_memory_error(global_data));
	if (!input->is_even)
		if (!philo_split_philosophers(global_data))
			return (philo_memory_split_error(global_data));
	return (philo_normal_execution(input, global_data));
}*/

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
