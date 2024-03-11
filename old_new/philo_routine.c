/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:16:32 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/11 15:08:17 by fporciel         ###   ########.fr       */
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
 * This part of the program is the philosophers' routine.
 */

#include "philo.h"

static void	philo_eat_and_release(t_philo *p)
{
	pthread_mutex_lock(p->timestamp);
	pthread_mutex_lock(p->stdout_mutex);
	if (philo_timestamp() < (p->intern_last_meal + p->time_to_die))
		printf("[%lu] %lu %s\n", philo_timestamp(), p->id, EAT);
	else
		p->intern_last_meal = 0;
	pthread_mutex_unlock(p->stdout_mutex);
	usleep(p->time_to_eat * 1000);
	if (p->intern_last_meal != 0)
	{
		*p->last_meal = philo_timestamp();
		p->intern_last_meal = *p->last_meal;
	}
	pthread_mutex_unlock(p->timestamp);
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
}

static void	philo_take_forks(t_philo *p)
{
	pthread_mutex_lock(p->forks_mutex);
	pthread_mutex_lock(p->right_fork);
	pthread_mutex_lock(p->stdout_mutex);
	if (philo_timestamp() < (p->intern_last_meal + p->time_to_die))
		printf("[%lu] %lu %s\n", philo_timestamp(), p->id, FORK);
	else
		p->intern_last_meal = 0;
	pthread_mutex_unlock(p->stdout_mutex);
	pthread_mutex_lock(p->left_fork);
	pthread_mutex_lock(p->stdout_mutex);
	if (philo_timestamp() < (p->intern_last_meal + p->time_to_die))
		printf("[%lu] %lu %s\n", philo_timestamp(), p->id, FORK);
	else
		p->intern_last_meal = 0;
	pthread_mutex_unlock(p->stdout_mutex);
	pthread_mutex_unlock(p->forks_mutex);
}

static void	*philo_unlimited(t_philo *p)
{
	while (1)
	{
		if (p->intern_last_meal == 0)
			return (NULL);
		philo_take_forks(p);
		philo_eat_and_release(p);
		pthread_mutex_lock(p->stdout_mutex);
		if (philo_timestamp() < (p->intern_last_meal + p->time_to_die))
			printf("[%lu] %lu %s\n", philo_timestamp(), p->id, SLEEP);
		else
			p->intern_last_meal = 0;
		pthread_mutex_unlock(p->stdout_mutex);
		usleep(p->time_to_sleep * 1000);
		pthread_mutex_lock(p->stdout_mutex);
		if (philo_timestamp() < (p->intern_last_meal + p->time_to_die))
			printf("[%lu] %lu %s\n", philo_timestamp(), p->id, THINK);
		else
			p->intern_last_meal = 0;
		pthread_mutex_unlock(p->stdout_mutex);
	}
	return (NULL);
}

static void	*philo_limited(t_philo *p)
{
	pthread_mutex_lock(p->stdout_mutex);
	printf("LIMITED: %lu\n", p->number_of_meals);
	pthread_mutex_unlock(p->stdout_mutex);
	while (p->number_of_meals--)
	{
		pthread_mutex_lock(p->stdout_mutex);
		printf("LIMITED: %lu\n", p->number_of_meals);
		pthread_mutex_unlock(p->stdout_mutex);
		if (p->intern_last_meal == 0)
			return (NULL);
		philo_take_forks(p);
		philo_eat_and_release(p);
		pthread_mutex_lock(p->stdout_mutex);
		if (philo_timestamp() < (p->intern_last_meal + p->time_to_die))
			printf("[%lu] %lu %s\n", philo_timestamp(), p->id, SLEEP);
		else
			p->intern_last_meal = 0;
		pthread_mutex_unlock(p->stdout_mutex);
		usleep(p->time_to_sleep * 1000);
		pthread_mutex_lock(p->stdout_mutex);
		if (philo_timestamp() < (p->intern_last_meal + p->time_to_die))
			printf("[%lu] %lu %s\n", philo_timestamp(), p->id, THINK);
		else
			p->intern_last_meal = 0;
		pthread_mutex_unlock(p->stdout_mutex);
	}
	pthread_mutex_lock(p->timestamp);
	*p->last_meal = p->intern_last_meal + p->time_to_die + 1000;
	pthread_mutex_unlock(p->timestamp);
	return (NULL);
}

void	*philo_routine(void *info)
{
	t_philo	*p;

	p = (t_philo *)info;
	pthread_mutex_lock(p->start_mutex);
	pthread_mutex_unlock(p->start_mutex);
	pthread_mutex_lock(p->timestamp);
	*p->last_meal = philo_timestamp();
	p->intern_last_meal = *p->last_meal;
	pthread_mutex_unlock(p->timestamp);
	if (p->number_of_meals)
		return (philo_limited(p));
	else
		return (philo_unlimited(p));
}
