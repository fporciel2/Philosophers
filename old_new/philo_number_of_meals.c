/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_number_of_meals.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:04:50 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/10 10:19:35 by fporciel         ###   ########.fr       */
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
 * This part of the program converts the input parameter 
 * 'number_of_times_each_philosopher_must_eat' into an integer or notes an error
 * in it.
 */

#include "philo.h"

static int	philo_invalidate(t_input *input)
{
	input->is_valid = 0;
	input->badnotepme = BADNOTEPME;
	return (0);
}

static ssize_t	philo_notepmelen(char *str, t_input *input)
{
	ssize_t	len;

	len = 0;
	if (str)
	{
		while (str[len])
		{
			if (str[len] < 48 || str[len] > 57)
			{
				input->is_valid = 0;
				input->badnotepme = BADNOTEPME;
				return (-1);
			}
			len++;
		}
	}
	if (len > 20)
	{
		input->is_valid = 0;
		input->badnotepme = BADNOTEPME;
		return (-1);
	}
	return (len);
}

static int	philo_is_integer(char *str1, char *str2, t_input *input)
{
	ssize_t	i;
	ssize_t	j;
	int		all_equal;

	if (str1[0] > str2[0])
		return (philo_invalidate(input));
	i = 1;
	all_equal = 1;
	while (str1[i] && all_equal)
	{
		j = 0;
		while (j < i)
		{
			if (str1[j] == str2[j])
				all_equal = 1;
			else
				all_equal = 0;
			j++;
		}
		if (all_equal && (str1[i] > str2[i]))
			return (philo_invalidate(input));
		i++;
	}
	return (1);
}

static uint64_t	philo_atolui(char *str, ssize_t len)
{
	uint64_t	i;
	uint64_t	result;
	uint64_t	power_of_ten;
	uint64_t	j;

	i = 0;
	result = 0;
	len--;
	power_of_ten = 10;
	while (len > 0)
	{
		j = len;
		while (j - 1)
		{
			power_of_ten *= 10;
			j--;
		}
		result += (str[i] - 48) * power_of_ten;
		i++;
		len--;
		power_of_ten = 10;
	}
	result += (str[i] - 48);
	return (result);
}

void	philo_number_of_meals(char *str, t_input *input)
{
	ssize_t	len;

	len = philo_notepmelen(str, input);
	if ((len < 0) || ((len == 20) && !philo_is_integer(str, AINT64MAX, input)))
		return ;
	input->number_of_meals = philo_atolui(str, len);
	if (input->number_of_meals == 0)
		input->is_special = 1;
	input->is_limited = 1;
}
