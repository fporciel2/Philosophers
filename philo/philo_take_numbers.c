/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_take_numbers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:49:38 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/28 11:05:18 by fporciel         ###   ########.fr       */
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
 * This part of the program checks the validity of the number of philosophers
 * and the number of times each philosopher must eat passed to the program as
 * arguments. It checks the number of philosophers against the maximum number of
 * threads allowed by the system using the macro MAXPHILOS as a limit, and
 * checks that the number of times each philosopher must eat is minor than
 * INT64_MAX.
 */

#include "philo.h"

static int	philo_number_of_times_each_philosopher_must_eat(
		uint64_t *number_of_times_each_philosopher_must_eat, char *str)
{
	*number_of_times_each_philosopher_must_eat = philo_atolui(str);
	if ((*number_of_times_each_philosopher_must_eat == INT64_MAX)
		|| (*number_of_times_each_philosopher_must_eat == 0))
		return (0);
	return (1);
}

static int	philo_number_of_philosophers(uint64_t *number_of_philosophers,
		char *str)
{
	*number_of_philosophers = philo_atolui(str);
	if ((*number_of_philosophers == INT64_MAX)
		|| (*number_of_philosophers > MAXPHILOS)
		|| (*number_of_philosophers == 0))
		return (0);
	return (1);
}

int	philo_take_numbers(t_input *input, char **argv, int argc)
{
	if (!philo_number_of_philosophers(&input->number_of_philosophers, argv[1]))
		return (0);
	if (argc == 6)
		return (philo_number_of_times_each_philosopher_must_eat(
				&input->number_of_times_each_philosopher_must_eat, argv[5]));
	return (1);
}
