/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sit_at_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:29:54 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/25 15:12:54 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* Philosophers is a simulation that implements a solution to the dining
 * philosophers problem in C. This version is not ready to use and it is not
 * safe to use.
 * This is the implementation of the table with spaghetti.
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
 * SIT AT TABLE
 *
 * One or more philosophers sit at a round table. There is a large bowl of
 * spaghetti in the middle of the table.
 */

#include "philo.h"

static uint64_t	philo_count_philosophers(t_philo *philosophers)
{
	uint64_t	i;

	i = 0;
	if (philosophers)
	{
		while (philosophers[i].is != 0)
			i++;
	}
	return (i);
}

static t_table	*philo_create_table(t_table *table, uint64_t number)
{
	uint64_t	i;

	i = 0;
	table = (t_table *)malloc(sizeof(t_table) * number);
	if (table == NULL)
		return (NULL);
	if (number != 1)
	{
		while (i < (number - 1))
		{
			table[i].table = table;
			table[i].next = &table[i + 1];
			i++;
		}
	}
	table[i].table = table;
	table[i].next = &table[0];
	return (table);
}

t_table	*philo_sit_at_table(t_philo *philosophers)
{
	t_table		*table;
	t_bowl		*spaghetti;
	uint64_t	number_of_philosophers;
	uint64_t	i;

	number_of_philosophers = philo_count_philosophers(philosophers);
	if (number_of_philosophers == 0)
		return (NULL);
	table = philo_create_table(NULL, number_of_philosophers);
	if (table == NULL)
		return (NULL);
	spaghetti = (t_bowl *)malloc(sizeof(t_bowl));
	if (spaghetti == NULL)
		return (free(table), NULL);
	i = 0;
	while (i < number_of_philosophers)
	{
		table[i].philosopher = &philosophers[i];
		table[i].spaghetti = spaghetti;
	}
	return (table);
}
