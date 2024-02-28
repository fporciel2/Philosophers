/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_atolui.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:08:22 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/28 11:01:22 by fporciel         ###   ########.fr       */
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
 * This part of the program converts a string into an integer with type
 * 'uint64_t': it compares the string against AINT64MAX, that is a constant
 * string representing the maximum value for a 'uint64_t' integer by checking
 * its length and its values. If the comparison has positive outcome, it
 * converts the string.
 */

#include "philo.h"

static uint64_t	philo_atolui_exec(char *str, size_t len)
{
	size_t		i;
	uint64_t	result;
	uint64_t	power_of_ten;

	i = len;
	result = 0;
	power_of_ten = 10;
	i--;
	while (i)
	{
		power_of_ten *= 10;
		i--;
	}
	len--;
	i = 0;
	while (len)
	{
		result += ((str[i] - 48) * power_of_ten);
		power_of_ten /= 10;
		len--;
		i++;
	}
	result += (str[i] - 48);
	return (result);
}

static int	philo_is_smaller_than_aintmax(char *str1, char *str2, size_t len)
{
	size_t	i;

	i = 0;
	while (str1[i])
	{
		if ((str[i] < 48) || (str[i] > 57)
			|| ((len == 20) && (str1[i] >= str2[i])))
			return (0);
		i++;
	}
	return (1);
}

uint64_t	philo_atolui(char *str)
{
	size_t	len;

	len = 0;
	if (str)
	{
		while (str[len])
			len++;
	}
	if ((len > 20) || !philo_is_smaller_than_aintmax(str, AINT64MAX, len))
		return (INT64_MAX);
	return (philo_atolui_exec(str, len));
}
