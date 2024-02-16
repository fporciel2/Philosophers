/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:10:24 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/16 14:27:03 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* This file is part of the Philosophers project. Its purpose is to provide
 * modular functions used by the threads.
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
 * Header inclusion.
 */

#include "philo.h"
/*
 * The function 'philo_log' is meant to display the current status of a
 * philosopher.
 */

int	philo_log(uint64_t tmstmp, uint64_t id, char *status)
{
	return (printf("[%lu] Philosopher %lu %s\n", tmstmp, id, status));
}
/*
 * The function 'get_time' is meant to take the current timestamp in
 * milliseconds.
 */

uint64_t	philo_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((uint64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}
