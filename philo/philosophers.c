/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:29:50 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/11 14:23:11 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* This program is part of the Philosophers project. Its purpose is to simulate
 * the life of a group of philosophers using threads. It is written in C. It is
 * an implementation of a solution of the Dining Philosophers problem.
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
 * This is the main file of the Philosophers program. It contains the main
 * function.
 *
 * First of all, it includes the header file of the program.
 */
#include "philo.h"
/*
 * The main function implements the program's routine. 
 *
 * As said you can see in 'philo_input_check.c', the first step taken by the
 * program is to parse the input received as an argument in order to check its
 * validity. To do so, the value of the number of arguments is decreased by 1 to
 * exclude the program's name, and then checked to be greater than 3 and minor
 * than 6 as an ensure that the values represent only the valid parameters
 * 'number_of_philosophers', 'time_to_die', 'time_to_eat', 'time_to_sleep' or
 * those four parameters plus 'number_of_times_each_philosopher_must_eat'. If
 * this test is not passed, an error message advises the user of the error and 
 * exits. Otherwise, the program will continue by parsing the validity of each
 * parameter using the function 'philo_parse'. The variable 'input' is created
 * to point the memory area where the integer values corresponding to the input
 * will be stored, i.e. a static array of size 5*sizeof (uint64_t).
 */

int	main(int argc, char **argv)
{
	static uint64_t	input[5];

	argc--;
	if (argc < 4 || argc > 5)
		return (write(2, "Wrong number of arguments.\n", 27) > 0);
	argv++;
	philo_parse(argc, argv, input);
	if ((input[0] == 0) && (input[1] == 0) && (input[2] == 0)
		&& (input[3] == 0))
		return (write(2, "Wrong input.\n", 13) > 0);
}
