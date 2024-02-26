/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clean_table.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:15:14 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/26 10:30:09 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* Philosophers is a simulation that implements a solution to the dining
 * philosophers problem in C. This version is not ready to use and it is not
 * safe to use.
 * This is the cleaner for the table and the bowl of spaghetti.
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
 */

#include "philo.h"

t_table	*philo_clean_table(t_table *table)
{
	if (table)
	{
		if (table->spaghetti)
		{
			if (table->spaghetti->is_getting_eaten)
				free(table->spaghetti->is_getting_eaten);
			free(table->spaghetti);
		}
		free(table);
	}
	return (NULL);
}
