/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:18:52 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/09 12:51:42 by fporciel         ###   ########.fr       */
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
 * This part of the program executes the lifecycle of each philosopher, apart
 * from the last one with an odd number of philosophers, which is executed by
 * the philo_last_routine.c code path.
 */

#include "philo.h"

static int	philo_sleep(t_philo *philo)
{
	if (!philo_log_sleep(philo)
		|| (usleep(philo->time_to_sleep * 1000) < 0))
		return (0);
	pthread_mutex_lock(philo->timestamp);
	if ((philo_timestamp() >= (*philo->last_meal + philo->time_to_die))
		|| ((philo_timestamp() + philo->time_to_eat)
			>= (*philo->last_meal + philo->time_to_die))
		|| ((philo_timestamp() + philo->time_to_sleep)
			>= (*philo->last_meal + (uint64_t)philo->time_to_die)))
		return (philo_death(philo, 2));
	pthread_mutex_unlock(philo->timestamp);
	pthread_mutex_lock(philo->stdout_mutex);
	if (philo_timestamp() < (*philo->last_meal + philo->time_to_die))
		printf("[%lu] %lu %s\n", philo_timestamp(), philo->id, THINK);
	pthread_mutex_unlock(philo->stdout_mutex);
	return (1);
}

static int	philo_eat(t_philo *philo, uint64_t eat_time)
{
	if (!philo_take_forks(philo)
		|| !philo_log_eat(philo)
		|| (usleep(eat_time * 1000) < 0)
		|| !philo_release_forks(philo))
		return (0);
	return (1);
}

static void	*philo_limited_routine(t_philo *philo, uint64_t eat_time)
{
	while (philo->number_of_meals)
	{
		if (!philo_eat(philo, eat_time) || !philo_sleep(philo))
			return (NULL);
		philo->number_of_meals--;
	}
	return (NULL);
}

static void	*philo_unlimited_routine(t_philo *philo, uint64_t eat_time)
{
	while (1)
	{
		if (!philo_eat(philo, eat_time) || !philo_sleep(philo))
			return (NULL);
	}
	return (NULL);
}

void	*philo_routine(void *philosopher)
{
	t_philo		*philo;
	uint64_t	eat_time;

	philo = (t_philo *)philosopher;
	eat_time = philo->time_to_eat;
	if ((philo->number_of_philosophers % 2)
		&& (philo->id >= (philo->number_of_philosophers - 2)))
		philo->time_to_eat *= 2;
	pthread_mutex_lock(philo->stdout_mutex);
	printf("Time to eat: %lu\n", philo->time_to_eat);
	pthread_mutex_unlock(philo->stdout_mutex);
	pthread_mutex_lock(philo->start_mutex);
	pthread_mutex_lock(philo->timestamp);
	*philo->last_meal = philo_timestamp();
	pthread_mutex_unlock(philo->timestamp);
	pthread_mutex_unlock(philo->start_mutex);
	pthread_mutex_lock(philo->stdout_mutex);
	printf("Starting time: %lu\n", *philo->last_meal);
	pthread_mutex_unlock(philo->stdout_mutex);
	if (philo->number_of_meals == 0)
		return (philo_unlimited_routine(philo, eat_time));
	else
		return (philo_limited_routine(philo, eat_time));
	return (NULL);
}
