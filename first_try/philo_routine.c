/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 09:34:03 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/19 11:02:57 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* This file is part of the Philosophers project. It contains the main routine,
 * i.e. the philosopher's routine.
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
 * This file works using the 't_t' data type, passed to 'philo_routine' from the
 * 'philo_timer.c' code path.
 typedef struct s_t
{
	pthread_mutex_t	*table;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*time;
	uint64_t		id;
	uint64_t		*start_time;
	uint64_t		ttd;
	uint64_t		tte;
	uint64_t		tts;
	uint64_t		nte;
	int				*iseating;
	int				*end;
}					t_t;
 *
 * The general purpose of this structure and the functions in this file is to
 * establish a routine consistent with the synchronization algorithm adopted.
 * The synchronization algorithm adopted is a variant of the resource hierarchy
 * solution. 
 * The algorithm is:
 * 1 - The philosopher takes the infinite code path if the value of 't->nte' is
 * 0, the finite code path otherwise: the difference between the infinite and
 * finite code path is that the infinite code path uses a 'while true' loop,
 * while the finite code path uses a 'while' loop that ends after 't->nte'
 * iterations. In any case, the while loop works as follows;
 * 2 - The philosopher locks the table, displays the message logging that it is
 * thinking, and then unlocks the table.
 * 3 - The philosopher locks the left fotk, locks the table, displays the
 * message logging that it has taken a fork, and then unlocks the table;
 * 4 - The philosopher locks the right fork, displays the message logging that
 * it has taken a fork, and then unlocks the table;
 * 5 - The philosopher locks the time, locks the table, displays the message
 * logging that it is eating, sets the value of '*t->iseating' to 1, unlocks the
 * table and unlocks the time;
 * 6 - The philosopher waits for 't->tte' milliseconds;
 * 7 - The philosopher locks the time, assigns the current timestamp to
 * '*t->start_time', sets the value of '*t->iseating' to 0, unlocks the time and
 * unlocks both forks;
 * 8 - The philosopher locks the table, displays the message logging that it 
 * is sleeping, and then unlocks the table;
 * 9 - The philosopher waits for 't->tts' milliseconds;
 * 10 - If the loop is over due to the finite code path, the philosopher locks
 * the time, assigns the value 1 to '*t->end', unlocks the time and waits for
 * 't->ttd' milliseconds until it its end.
 * Obviously, the most important part of this file is the inclusion of the holy
 * header.
 */

#include "philo.h"
/*
 * The 'philo_continue_routine' is here merely for readability: is continues the
 * cycle of both the finite and infinite code paths.
 */

static void	philo_continue_routine(t_t *t)
{
	pthread_mutex_lock(t->time);
	pthread_mutex_lock(t->table);
	philo_log(philo_get_time(), t->id, EATING);
	*(t->iseating) = 1;
	pthread_mutex_unlock(t->table);
	pthread_mutex_unlock(t->time);
	usleep(t->tte * 1000);
	pthread_mutex_lock(t->time);
	*(t->start_time) = philo_get_time();
	*(t->iseating) = 0;
	pthread_mutex_unlock(t->time);
	pthread_mutex_unlock(t->left_fork);
	pthread_mutex_unlock(t->right_fork);
	pthread_mutex_lock(t->table);
	philo_log(philo_get_time(), t->id, SLEEPING);
	pthread_mutex_unlock(t->table);
	usleep(t->tts * 1000);
}

static void	*philo_routine_finite(t_t *t)
{
	while ((t->nte)-- > 0)
	{
		pthread_mutex_lock(t->table);
		philo_log(philo_get_time(), t->id, THINKING);
		pthread_mutex_unlock(t->table);
		pthread_mutex_lock(t->left_fork);
		pthread_mutex_lock(t->table);
		philo_log(philo_get_time(), t->id, FORK);
		pthread_mutex_unlock(t->table);
		pthread_mutex_lock(t->right_fork);
		pthread_mutex_lock(t->table);
		philo_log(philo_get_time(), t->id, FORK);
		pthread_mutex_unlock(t->table);
		philo_continue_routine(t);
	}
	pthread_mutex_lock(t->time);
	*(t->end) = 1;
	usleep(t->ttd * 1000);
	pthread_mutex_unlock(t->time);
	return (NULL);
}
/*
 * The 'philo_routine_infinite' function immediately starts the 'while true'
 * cycle.
 */

static void	*philo_routine_infinite(t_t *t)
{
	while (1)
	{
		pthread_mutex_lock(t->table);
		philo_log(philo_get_time(), t->id, THINKING);
		pthread_mutex_unlock(t->table);
		pthread_mutex_lock(t->left_fork);
		pthread_mutex_lock(t->table);
		philo_log(philo_get_time(), t->id, FORK);
		pthread_mutex_unlock(t->table);
		pthread_mutex_lock(t->right_fork);
		pthread_mutex_lock(t->table);
		philo_log(philo_get_time(), t->id, FORK);
		pthread_mutex_unlock(t->table);
		philo_continue_routine(t);
	}
	return (NULL);
}
/*
 * The 'philo_routine' function begins by "un-casting" the 't' structure.
 * Then, it checks the value of 't->nte'. If it is 0, the infinite code path is
 * taken, otherwise, the finite code path is taken.
 */

void	*philo_routine(void *t_struct)
{
	t_t	*t;

	t = (t_t *)t_struct;
	if (t->nte == 0)
		return (philo_routine_infinite(t));
	else
		return (philo_routine_finite(t));
}
