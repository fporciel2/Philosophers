/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:18:52 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/07 18:13:25 by fporciel         ###   ########.fr       */
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
	if (!philo_log_sleep(philo) || (usleep(philo->time_to_sleep * 1000) < 0))
		return (-1);
	pthread_mutex_lock(philo->stdout_mutex);
	if (philo_timestamp() < (*philo->last_meal + philo->time_to_die))
		printf("[%lu] %lu %s\n", philo_timestamp(), philo->id, THINK);
	pthread_mutex_unlock(philo->stdout_mutex);
	if ((philo->number_of_philosophers % 2)
		&& (philo->id >= (philo->number_of_philosophers - 2)))
		philo_last_routine(philo);
	return (1);
}

static int	philo_eat(t_philo *philo)
{
	if (!philo_take_fork(philo, philo->right_fork, 0)
		|| !philo_take_fork(philo, philo->left_fork, 1)
		|| !philo_log_eat(philo)
		|| (usleep(philo->time_to_eat * 1000) < 0)
		|| !philo_release_forks(philo))
		return (0);
	return (1);
}

static void	*philo_limited_routine(t_philo *philo)
{
	pthread_mutex_t	*tmp;

	while (philo->number_of_meals)
	{
		pthread_mutex_lock(philo->stdout_mutex);
		printf("%lu : %p\n", philo->id, (void *)philo->right_fork);
		pthread_mutex_unlock(philo->stdout_mutex);
		if (!philo->right_fork)
		{
			usleep(philo->time_to_eat * 1000);
			tmp = philo->right_fork;
			philo->right_fork = philo->third_fork;
			philo->third_fork = tmp;
			continue ;
		}
		else if (!philo_eat(philo) || (philo_sleep(philo) < 0))
			return (NULL);
		philo->number_of_meals--;
	}
	return (NULL);
}

static void	*philo_unlimited_routine(t_philo *philo)
{
	pthread_mutex_t	*tmp;

	while (1)
	{
		if (!philo->right_fork)
		{
			usleep(philo->time_to_eat * 1000);
			tmp = philo->right_fork;
			philo->right_fork = philo->third_fork;
			philo->third_fork = tmp;
			continue ;
		}
		else if (!philo_eat(philo) || (philo_sleep(philo) < 0))
			return (NULL);
	}
	return (NULL);
}

void	*philo_routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	pthread_mutex_lock(philo->is_over_mutex);
	pthread_mutex_lock(philo->timestamp);
	*philo->last_meal = philo_timestamp();
	pthread_mutex_unlock(philo->timestamp);
	pthread_mutex_unlock(philo->is_over_mutex);
	if (philo->number_of_meals == 0)
		return (philo_unlimited_routine(philo));
	else
		return (philo_limited_routine(philo));
	return (NULL);
}
