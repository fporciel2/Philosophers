/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_time.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 09:49:24 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/11 10:40:34 by fporciel         ###   ########.fr       */
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
 * This part of the program converts each of the 'time_to_*' into the
 * corresponding integer or notes an error in it.
 */

#include "philo.h"

static int	philo_time_len(char *str, size_t *len)
{
	while (str[*len])
	{
		if ((str[*len] < 48) && (str[*len] > 57))
			return (0);
		(*len)++;
	}
	if (*len > 4)
		return (0);
	return (1);
}

static useconds_t	philo_atousec(char *str, size_t len)
{
	if (len == 1)
		return (str[0] - 48);
	else if (len == 2)
		return ((str[0] - 48) * 10 + (str[1] - 48));
	else if (len == 3)
		return ((str[0] - 48) * 100 + (str[1] - 48) * 10 + (str[2] - 48));
	else
		return ((str[0] - 48) * 1000 + (str[1] - 48) * 100 + (str[2] - 48) * 10
			+ (str[3] - 48));
}

void	philo_init_time(char *str, t_input *input, int param)
{
	size_t	len;

	len = 0;
	if (!philo_time_len(str, &len) || ((len == 4) && ((str[0] > 49)
				|| (str[1] > 48) || (str[2] > 48) || (str[3] > 48))))
	{
		input->is_valid = 0;
		if (param == 0)
			input->badttd = BADTTD;
		else if (param == 1)
			input->badtte = BADTTE;
		else
			input->badtts = BADTTS;
		return ;
	}
	if (param == 0)
		input->time_to_die = philo_atousec(str, len);
	else if (param == 1)
		input->time_to_eat = philo_atousec(str, len);
	else
		input->time_to_sleep = philo_atousec(str, len);
}
