/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_take_times.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:17:33 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/28 11:53:28 by fporciel         ###   ########.fr       */
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
 * This part of the program checks the validity of the times passed as
 * parameters. It checks whether the times are greater or equal than 0 an less
 * than 1000 milliseconds ( == 1000000 microseconds), that is the greater value
 * allowed for 'useconds_t' in most systems.
 */

#include "philo.h"

static useconds_t	philo_atousec_exec(char *str, size_t len)
{
	size_t		i;
	useconds_t	result;
	useconds_t	power_of_ten;

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
	return (result * 1000);
}

static int	philo_atousec_compare(char *str, size_t len)
{
	if (len == 4)
	{
		if ((str[0] > 49) || (str[1] > 48) || (str[2] > 48) || (str[3] > 48))
			return (0);
	}
	return (1);
}

static int	philo_atousec(useconds_t *time, char *str)
{
	size_t	len;

	len = 0;
	if (str)
	{
		while (str[len])
			len++;
	}
	if ((len > 4) || !philo_atousec_compare(str, len))
		return (0);
	*time = philo_atousec_exec(str, len);
	return (1);
}

int	philo_take_times(t_input *input, char **argv)
{
	if (!philo_atousec(&input->time_to_die, argv[2])
		|| !philo_atousec(&input->time_to_eat, argv[3])
		|| !philo_atousec(&input->time_to_sleep, argv[4]))
		return (0);
	return (1);
}
