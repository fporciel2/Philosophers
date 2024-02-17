/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_timer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:21:59 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/17 17:30:29 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* This file is part of the Philosophers project. It contains the routine of the
 * threads representing the timers of the philosophers.
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
 * The concept of the timer's routine is about the construction of a basic
 * logical clock for processes. While in this specific implementation it doesn't
 * work as a fully-implemented logical clock, it is a good starting point. A
 * full logical clock should establish the happen-before (or happen-after)
 * relation between events occurring in processes. There are two limitations to
 * that purpose: philosophers can't communicate, so the threads can't share
 * memory and so events can't be logged to modify the behavior of other
 * processes. While this limitation is not too big, it involves a change of
 * concept. In order to implement a logical clock without communication between
 * processes, it is important to work in two phases: in a first phase, the Make
 * tool should check the system's situation. In a second phase, the compiler
 * should produce a system-dependent code path that allows to infer the
 * determinant of a state of degradation in the communication between events
 * starting from the self-detection, by a process, of the temporal variations in
 * its execution with respect to a pre-established temporal order, and adapt
 * accordingly. This require a metaprogramming approach and a theory of
 * communication between events that excludes communication between processes.
 * It can be done by retrieving Leibniz's theory of time, but I will not do it
 * now because the newtonian simulation of time is imprisoning my mind and I
 * feel like I have no time to do so. We will see that later.
 * Right now, the only thing to build is a timer that lays the foundation for
 * that kind of clock: it will check for the death of the philosopher,
 * establishing a basic timing for the child thread.
 * Another thing not done is proper error handling. Since this is a preliminary
 * phase of the project, I will not implement it. However, it is important to
 * note that this program is not ready-to-use. It can only show a limited range
 * of synchronization situations working well.
 */
/* Header inclusion. See 'philo.h' for more details about the structures used
 * int this file.*/

#include "philo.h"
/*
 * The 'philo_timer_clock' function simulates a clock that constantly checks the
 * current timestamp against the time of the last meal.
 */
/*
 * The 'philo_timer_init' function performs the creation of the philosophers. It
 * uses the variant of the resource hierarchy algorithm mentioned below in the
 * the description of the 'philo_timer' function as a criterion to choose
 * whether start the thread using the 'philo_routine_even' or the
 * 'philo_routine_odd' function. It also creates the 'time' mutex and retrieves
 * the pointer to the 'table' mutex in order to interact with the standard
 * output and the philosopher without interfering with their critical sections.
 * The 'phi' structure is initialized for readability and mutual exclusion
 * purposes.
 */

static void	*philo_timer_init(t_t *t, pthread_t *philosopher)
{
	pthread_mutex_t	*table;
	pthread_mutex_t	time;

	table = t->table;
	pthread_mutex_init(&time, NULL);
	t->time = &time;
	if (((t.id % 2) == 0) || (((p->input[0] % 2) != 0)
		&& (t.id == p->input[0])))
		pthread_create(philosopher, NULL, philo_routine_even, (void *)t);
	else
		pthread_create(philosopher, NULL, philo_routine_odd, (void *)t);
	return (philo_timer_clock(t, philosopher, table, &time));
}
/*
 * Due to the complexity of the timer's routine, a mutual-exclusive use of
 * resources is needed. To do so, the 'philo_timer' function takes a set of
 * pointers from the structure 'p', that is shared with the main process and
 * with other timers. To do so, it before locks the table: so, its execution
 * starts after the creation of all the other timers.
 * It also uses the 't' data type to perform an analogue communication with its
 * philosopher. After the exchange of addresses, there is no need to maintain a
 * reference to the 'phi' structure.
 * A note about the assignment of the forks. The basic way to synchronize the
 * philosophers is to apply a strict mutual exclusion through a variant of the
 * resource hierarchy algorithm, so that for any couple of philosophers the one
 * with odd id takes its fork before and then the fork of its companion, and the
 * even one does the opposite. With odd philosophers on the table, the last
 * philosopher has not a companion, so it must take the fork from the last even
 * philosopher.
 */

void	*philo_timer(void *phi)
{
	t_p			*p;
	pthread_t	*philosopher;
	static t_t	t;

	pthread_mutex_lock((t_p *)phi->table);
	p = (t_p *)phi;
	t.table = p->table;
	t.id = p->i + 1;
	if (((t.id % 2) == 0) || (((p->input[0] % 2) != 0)
		&& (t.id == p->input[0])))
		t.left_fork = p->forks[p->i - 1];
	else
		t.left_fork = p->forks[p->i];
	if (((t.id % 2) == 0) || (((p->input[0] % 2) != 0)
		&& (t.id == p->input[0])))
		t.right_fork = p->forks[p->i];
	else
		t.right_fork = p->forks[p->i - 1];
	t.ttd = p->input[1];
	t.tte = p->input[2];
	t.tts = p->input[3];
	t.nte = p->input[4];
	philosopher = &p->philosophers[p->i];
	pthread_mutex_unlock((t_p *)phi->table);
	return (philo_timer_init(&t, philosopher));
}
