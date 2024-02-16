/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_timer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:21:59 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/16 16:06:26 by fporciel         ###   ########.fr       */
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
/* Header inclusion. */

#include "philo.h"
/*
 * The 'philo_timer_odd' function is used to create the odd philosophers. Its
 * purpose is to assign the 'right_fork' and the 'left_fork' before starting the
 * thread.
 * In this case, the right fork is the fork corresponding to the philosopher
 * being created, and the left fork is the one of the next philosopher. If the
 * thread creation fails, the thread attempts to kill itself by calling the
 * 'philo_selfjoin' function.
 */

static void	*philo_timer_odd(t_t *t, t_p *p)
{
	pthread_mutex_lock(&p->forks[p->i]);
	pthread_mutex_lock(&p->forks[p->i + 1]);
	t->left_fork = &p->forks[p->i];
	t->right_fork = &p->forks[p->i + 1];
	pthread_mutex_unlock(&p->forks[p->i]);
	pthread_mutex_unlock(&p->forks[p->i + 1]);
	if (p->input[4] != 0)
	{
		if (pthread_create(philosophers[p->i], NULL, philo_odd_routine_nte,
			(void *)t) != 0)
			return (philo_selfjoin(t, p));
	}
	else
	{
		if (pthread_create(philosophers[p->i], NULL, philo_odd_routine_no_nte,
			(void *)t) != 0)
			return (philo_selfjoin(t, p));
	}
	return (philo_timer_clock(t, p));
}
/*
 * The 'philo_timer_even' function is used to create the even philosophers. Its
 * purpose is to assign the 'right_fork' and the 'left_fork' before starting the
 * thread.
 * In this case, the right fork is the fork corresponding to the philosopher
 * with the previous ID. If the thread creation fails, the thread attempts to
 * kill itself by calling the 'philo_selfjoin' function.
 */

static void	*philo_timer_even(t_t *t, t_p *p)
{
	pthread_mutex_lock(&p->forks[p->i - 1]);
	pthread_mutex_lock(&p->forks[p->i]);
	t->left_fork = &p->forks[p->i - 1];
	t->right_fork = &p->forks[p->i];
	pthread_mutex_unlock(&p->forks[p->i]);
	pthread_mutex_unlock(&p->forks[p->i - 1]);
	if (p->input[4] != 0)
	{
		if (pthread_create(philosophers[p->i], NULL, philo_even_routine_nte,
			(void *)t) != 0)
			return (philo_selfjoin(t, p));
	}
	else
	{
		if (pthread_create(philosophers[p->i], NULL, philo_even_routine_no_nte,
			(void *)t) != 0)
			return (philo_selfjoin(t, p));
	}
	return (philo_timer_clock(t, p));
}
/*
 * This is the main function of the timer's routine, 'philo_timer'. It starts by
 * locking the main mutex to ensure that the creation of other timers is going
 * well. After locking the mutex, it starts initializing the structure for the
 * philosopher. It assigns a different 'right_fork' and 'left_fork' depending on
 * the value of the 'id' of the philosopher: to do so, it splits its execution
 * accordingly.
 */

void	*philo_timer(void *philo)
{
	t_p			*p;
	t_t			t;
	uint64_t	start_time;

	pthread_mutex_lock(p->table);
	p = (t_p *)philo;
	t.id = p->i + 1;
	t.start_time = &start_time;
	t.table = p->table;
	pthread_mutex_unlock(p->table);
	t.ttd = p->input[1];
	t.tte = p->input[2];
	t.tts = p->input[3];
	t.nte = p->input[4];
	if (t.id != p->inpu[0])
	{
		if ((t.id % 2) == 0)
			return (philo_timer_even(&t, p));
		else
			return (philo_timer_odd(&t, p));
	}
	else
		return (philo_timer_even(&t, p));
}
