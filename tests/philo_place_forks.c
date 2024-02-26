/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_place_forks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:12:57 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/26 12:27:57 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* 'Philosophers' is a simulation that implements a solution to the dining
 * philosophers problem in C. This version is not ready to use and it is not
 * safe to use.
 * This file implements the part of the program in which the forks are placed on
 * the table.
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
 * PLACE_FORKS
 *
 * There are also forks on the table. There are as many forks as philosophers.
 */

#include "philo.h"

t_forks	*philo_clean_forks(t_forks *forks)
{
	if (forks)
		free(forks);
	return (NULL);
}

t_forks	*philo_place_forks(t_philo *philosophers, t_table *table)
{
	t_forks		*forks;
	uint64_t	i;
	uint64_t	j;

	i = 0;
	while (philosophers[i].is != 0)
		i++;
	forks = (t_forks *)malloc(sizeof(t_forks) * i);
	if (forks == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		table[j].forks = forks[j];
		j++;
	}
	return (forks);
}
/*This function is too easy to test.*/
