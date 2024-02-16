/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start_simulation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:24:22 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/16 09:52:31 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* This file is part of the Philosophers project. Its purpose is to start the
 * simulation by initializing the threads and the mutexes and then starting the
 * threads.
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
 * https://github.com/fporciel2
 */
/*
 * First thing to do, is to include the header file of the program. Nothing
 * else.
 */
#include "philo.h"
/*
 * The general purpose of 'philo_start_simulation' is to start the simulation.
 * To do so, two parameters are given: 'timers', which is a pointer to the
 * beginning of an array of threads that will be used to simulate the life cycle
 * of a philosopher, representing the "biological clock" of each philosopher;
 * 'input', which is a pointer to the beginning of an array containing since the
 * beginning the values 'number_of_philosophers', 'time_to_die', 'time_to_eat',
 * 'time_to_sleep' and eventually 'number_of_times_each_philosopher_must_eat'.
 * Then, another variable is created representing the mutex that will be used to
 * to lock the standard output: in this case, we will call it 'table'.
 */

int	philo_start_simulation(pthread_t *timers, uint64_t *input)
{
	pthread_mutex_t	table;
}
