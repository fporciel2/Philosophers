/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:55:14 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/28 12:22:46 by fporciel         ###   ########.fr       */
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
 * This part of the program initializes the variables used in the simulation and
 * starts the simulation.
 */

#include "philo.h"

static int	philo_uninit(t_philo *philosophers, t_fork *forks,
		t_tmstmp *timestamps)
{
	if (philosophers)
		free(philosophers);
	if (forks)
		free(forks);
	if (timestamps)
		free(timestamps);
	return (0);
}

static int	philo_init_data(t_philo *philosophers, t_fork *forks,
		t_tmstmp *timestamps, t_input *input)
{
	t_data	data;

	data.philosophers = philosophers;
	data.forks = forks;
	data.timestamps = timestamps;
	data.input = input;
	return (philo_start_simulation(&data));
}

static int	philo_label_arrays(t_philo *philosophers, t_fork *forks,
		t_tmstmp *timestamps, t_input *input)
{
	uint64_t	i;
	uint64_t	id;

	i = 0;
	id = 1;
	while (i < input->number_of_philosophers)
	{
		philosophers[i].id = id;
		forks[i].id = id;
		timestamps[i].id = id;
		id++;
		i++;
	}
	philosophers[i].id = 0;
	forks[i].id = 0;
	timestamps[i].id = 0;
	return (philo_init_data(philosophers, forks, timestamps, input));
}

int	philo_init(t_input *input)
{
	t_philo		*philosophers;
	t_fork		*forks;
	t_tmstmp	*timestamps;

	philosophers = (t_philo *)malloc(sizeof(t_philo)
			* (input->number_of_philosophers + 1));
	forks = (t_fork *)malloc(sizeof(t_fork)
			* (input->number_of_philosophers + 1));
	timestamps = (t_tmstmp *)malloc(sizeof(t_tmstmp)
			* (input->number_of_philosophers + 1));
	if (!philosophers || !forks || !timestamps)
		return (philo_uninit(philosophers, forks, timestamps));
	return (philo_label_arrays(philosophers, forks, timestamps, input));
}
