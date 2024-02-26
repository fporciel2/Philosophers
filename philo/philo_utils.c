/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:57:54 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/26 15:12:19 by fporciel         ###   ########.fr       */
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
 * This file contains some utilities.
 */

#include "philo.h"

void	philo_log(char *str, t_philo *philosopher)
{
	if (!philo_is_dead(philosopher))
	{
		pthread_mutex_lock(&philosopher->stdout_mutex);
		printf("%d %d %s\n", philo_get_time() - philosopher->last_time,
				philosopher->id, str);
		pthread_mutex_unlock(&philosopher->stdout_mutex);
	}
}

int	philo_get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	philo_sleep(int time, t_philo *philosopher)
{
	int	start;

	start = philo_get_time();
	while (((philo_get_time() - start) < time) && !philo_is_dead(philosopher))
		usleep(50);
}

int	philo_is_dead(t_philo *philosopher)
{
	return (philosopher->is_dead);
}
