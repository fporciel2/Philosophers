/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:44:05 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/10 15:11:03 by fporciel         ###   ########.fr       */
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
 * This part of the program contains the routines for each philosopher.
 */

#include "philo.h"

static int	philo_sleep(t_philo *philo)
{
	if (!philo_log(philo, SLEEP)
		|| (usleep(philo->time_to_sleep * 1000))
		|| !philo_log(philo, THINK))
		return (0);
	return (1);
}

static int	philo_eat(t_philo *philo)
{
	if (!philo_take_forks(philo)
		|| !philo_log(philo, EAT)
		|| (usleep(philo->time_to_eat * 1000))
		|| !philo_release_forks(philo))
		return (0);
	return (1);
}

static void	*philo_limited_routine(t_philo *philo)
{
	while (philo->number_of_meals)
	{
		if (!philo_eat(philo) || !philo_sleep(philo))
			return (NULL);
		philo->number_of_meals--;
	}
	pthread_mutex_lock(philo->timestamp);
	while (philo->number_of_philosophers)
	{
		usleep(philo->time_to_die * 1000);
		philo->number_of_philosophers--;
	}
	pthread_mutex_unlock(philo->timestamp);
	return (NULL);
}

static void	*philo_unlimited_routine(t_philo *philo)
{
	while (1)
	{
		if (!philo_eat(philo) || !philo_sleep(philo))
			return (NULL);
	}
	return (NULL);
}

void	*philo_routine(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	pthread_mutex_lock(philo->start_mutex);
	pthread_mutex_lock(philo->timestamp);
	*philo->last_meal = philo_timestamp();
	philo->intern_last_meal = *philo->last_meal;
	pthread_mutex_unlock(philo->timestamp);
	pthread_mutex_unlock(philo->start_mutex);
	if (philo->number_of_meals)
		return (philo_limited_routine(philo));
	return (philo_unlimited_routine(philo));
}
