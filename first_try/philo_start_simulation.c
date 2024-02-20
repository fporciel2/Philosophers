/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start_simulation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:24:22 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/20 12:26:27 by fporciel         ###   ########.fr       */
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
 * The function 'philo_destroy_mutexes' is nested into the file to destroy the
 * mutexes initialized before a mutex initialization failure and in general all
 * the mutexes allocated. It takes 'table', 'forks' and 'i' as parameters:
 * 'table' and 'forks' are the mutexes to destroy, 'i' is the number of mutexes
 * to destroy into the array whose beggining is pointed by 'forks'.
 */

static int	philo_destroy_mutexes(pthread_mutex_t *table,
		pthread_mutex_t *forks, uint64_t i)
{
	int			error_status;
	uint64_t	count;

	if (i == 0)
		return (0);
	error_status = 0;
	error_status = pthread_mutex_destroy(table);
	count = 0;
	while (count < i)
		error_status = pthread_mutex_destroy(&forks[count++]);
	return (error_status);
}
/*
 * Function 'philo_detach_threads' and 'philo_join_threads' are nested into the
 * file in order to, respectively, detach the timers if the thread creation
 * fails, or join the timers if the thread creation has success.
 * 'philo_join_threads' is also the end of the program.
 */

static int	philo_detach_threads(t_p *p, uint64_t i)
{
	int			error_status;
	uint64_t	count;

	if (i == 0)
		return (philo_destroy_mutexes(p->table, p->forks, p->input[0]));
	error_status = 0;
	count = 0;
	while (count < i)
		error_status = pthread_detach(p->timers[count++]);
	error_status = pthread_mutex_unlock(p->table);
	return (philo_destroy_mutexes(p->table, p->forks, p->input[0])
		|| error_status);
}

static int	philo_join_threads(t_p *p)
{
	uint64_t	i;
	int			error_status;

	i = 0;
	error_status = 0;
	while (i < p->input[0])
		error_status = pthread_join(p->timers[i++], NULL);
	return (philo_destroy_mutexes(p->table, p->forks, p->input[0])
		|| error_status);
}
/*
 * This function is meant to finish the boot of the simulation. After the
 * initialization of mutexes, the timers are created and, if thread creation
 * fails, detached. To do so, the 'table' is locked until all the timers are
 * created: if that does not happen, the previously created timers are detached.
 */

static int	philo_create_timers(t_p *p)
{
	uint64_t	i;

	i = 0;
	if (pthread_mutex_lock(p->table) != 0)
		return (philo_destroy_mutexes(p->table, p->forks, p->input[0]));
	while (i < p->input[0])
	{
		p->i = i;
		if (pthread_create(&p->timers[i], NULL, philo_timer, (void *)p) != 0)
			return (philo_detach_threads(p, i));
		i++;
	}
	if (pthread_mutex_unlock(p->table) != 0)
		return (philo_detach_threads(p, p->input[0]));
	return (philo_join_threads(p));
}
/*
 * The general purpose of 'philo_start_simulation' is to start the simulation.
 * To do so, two parameters are given: 'timers', which is a pointer to the
 * beginning of an array of threads that will be used to simulate the life cycle
 * of a philosopher, representing the "biological clock" of each philosopher;
 * 'input', which is a pointer to the beginning of an array containing since the
 * beginning the values 'number_of_philosophers', 'time_to_die', 'time_to_eat',
 * 'time_to_sleep' and eventually 'number_of_times_each_philosopher_must_eat'.
 * Then, other variables are created to store the mutexes. 'forks' will be
 * created store the mutexes that will be used to simulate the access to the
 * resources that represent the forks: no real resources will be used. Since I
 * apply a variant of the hierarchical resource algorithm, no philosopher will
 * take the second fork if he has not taken the first before, and no philosopher
 * will leave the forks before having taken both of them and eating. Since the
 * state of eating is changed by the advancement of time and the state of access
 * to the fork is delegated to the mutual exclusive synchronization, there is no
 * need to simulate the access to resource by creating physical resources.
 * 'table' is created to lock and unlock the standard output.
 */

int	philo_start_simulation(pthread_t *timers, uint64_t *input)
{
	static t_p				p;
	uint64_t				i;
	static pthread_t		philosophers[MAXPHILO];
	static pthread_mutex_t	forks[MAXPHILO];
	static pthread_mutex_t	table;

	p.table = &table;
	p.forks = forks;
	p.philosophers = philosophers;
	if (pthread_mutex_init(p.table, NULL) != 0)
		return ((int)write(2, "An error has occurred.\n", 23) >= 0);
	i = 0;
	while (i < input[0])
	{
		if (pthread_mutex_init(&p.forks[i], NULL) != 0)
			return (philo_destroy_mutexes(p.table, p.forks, i));
		i++;
	}
	p.timers = timers;
	p.input = input;
	return (philo_create_timers(&p));
}
