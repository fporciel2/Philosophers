/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_timer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:21:59 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/20 13:06:15 by fporciel         ###   ########.fr       */
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
 * The 'philo_timer_kill' function must cause the end of the dinner,
 * so all the resources must be released.
 * After that, the function checks whether it is killing the philosopher because
 * it is dead, or because the dinner is finished. To do so, it checks the value
 * of 'param' and if it is equal to 1, it logs the death of the philosopher.
 * In any case, it waits for '(time_to_die * 40) - 40' milliseconds before
 * detaching the philosopher. Since the 'usleep' function takes its arguments in
 * microseconds and the time to die is expressed in milliseconds, the value must
 * multiplied by 1000 to obtain the number of microseconds: however, 'usleep'
 * also has a maximum limit of 1000000 microseconds, so it is necessary to check
 * that the value is not greater than 1000000. However, in this implementation I
 * will not do it, because this is not the final version of the program and this
 * file simply shows the use of the 'usleep' function for small amounts of time.
 */

static void	*philo_timer_kill(pthread_t *philosopher, t_phi *phi, int param)
{
	useconds_t	time_to_kill;

	pthread_mutex_lock(phi->table);
	if (param == 1)
		param = philo_log(philo_get_time(), phi->id, DEAD);
	time_to_kill = (useconds_t)(phi->time_to_die * 1000);
	usleep(time_to_kill);
	usleep(time_to_kill);
	usleep(time_to_kill);
	usleep(time_to_kill - 40);
	pthread_detach(*philosopher);
	pthread_mutex_unlock(phi->time);
	pthread_mutex_destroy(phi->time);
	pthread_mutex_unlock(phi->table);
	return (NULL);
}
/*
 * The 'philo_timer_clock' function simulates a clock that constantly checks the
 * current timestamp against the time of the last meal.
 * The 'start_time' variable, that represents the beginning of the simulation in
 * terms of timestamp, or the timestamp of the last meal, is compared against
 * the current timestamp: if the difference between the current timestamp and
 * 'start_time' is greater or equal than 'time_to_die - 10', that represents the
 * final moment for the philosopher to live, it is then compared against the
 * '(time_to_die * 40) - 40' value, that represents the time of waiting before
 * killing the philosopher; if this comparison establishes that the difference
 * is greater than the killing time, then the philosopher is detached:
 * otherwise, the 'iseating' value is checked and, if it is equal to 0, the
 * killing process starts through the 'philo_timer_kill' function. Since it is
 * possible to for the philosopher to end its routine autonomously, this
 * circumstance is handled using the 'pthread_join' function under the condition
 * of a 'end' value equal to 1.
 */

static void	*philo_timer_clock(pthread_t *philosopher, t_phi *phi)
{
	pthread_mutex_lock(phi->time);
	phi->start_time = philo_get_time();
	pthread_mutex_unlock(phi->time);
	while (1)
	{
		pthread_mutex_lock(phi->time);
		if (phi->end == 1)
			break ;
		if ((philo_get_time() - phi->start_time) >= (phi->time_to_die - 10))
		{
			if ((philo_get_time() - phi->start_time) >= ((phi->time_to_die * 40)
					- 40))
				return (philo_timer_kill(philosopher, phi, 0));
			else if (phi->iseating == 0)
				return (philo_timer_kill(philosopher, phi, 1));
		}
		pthread_mutex_unlock(phi->time);
	}
	pthread_mutex_unlock(phi->time);
	pthread_join(*philosopher, NULL);
	return (NULL);
}
/*
 * The 'philo_timer_init' function performs the creation of the philosophers. It
 * uses the variant of the resource hierarchy algorithm mentioned below in the
 * the description of the 'philo_timer' function as a criterion to choose
 * whether start the thread using the 'philo_routine' function.
 * It also creates the 'time' mutex and retrieves
 * the pointer to the 'table' mutex in order to interact with the standard
 * output and the philosopher without interfering with their critical sections.
 * The 'phi' structure is initialized for readability and mutual exclusion
 * purposes. It is used to pass to the clock the variables that must be
 * constantly checked: passing them to the philosopher would cause constant
 * access to a shared critical section.
 */

static void	*philo_timer_init(t_t *t, pthread_t *philosopher)
{
	t_phi			phi;
	pthread_mutex_t	time;

	phi.table = t->table;
	pthread_mutex_init(&time, NULL);
	t->time = &time;
	phi.time = &time;
	phi.id = t->id;
	phi.time_to_die = t->ttd;
	t->start_time = &phi.start_time;
	t->iseating = &phi.iseating;
	t->end = &phi.end;
	pthread_create(philosopher, NULL, philo_routine, (void *)t);
	pthread_mutex_unlock(phi.table);
	return (philo_timer_clock(philosopher, &phi));
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
	t_t			t;

	pthread_mutex_lock(((t_p *)phi)->table);
	p = (t_p *)phi;
	t.table = p->table;
	t.id = p->i + 1;
	if (((t.id % 2) == 0) || (((p->input[0] % 2) != 0)
		&& (t.id == p->input[0])))
		t.left_fork = &p->forks[p->i - 1];
	else
		t.left_fork = &p->forks[p->i];
	if (((t.id % 2) == 0) || (((p->input[0] % 2) != 0)
		&& (t.id == p->input[0])))
		t.right_fork = &p->forks[p->i];
	else
		t.right_fork = &p->forks[p->i - 1];
	t.ttd = p->input[1];
	t.tte = p->input[2];
	t.tts = p->input[3];
	t.nte = p->input[4];
	philosopher = &p->philosophers[p->i];
	return (philo_timer_init(&t, philosopher));
}
