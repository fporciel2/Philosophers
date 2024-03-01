/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:53:45 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/01 11:24:26 by fporciel         ###   ########.fr       */
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
 * This part of the program gives the main codepath.
 */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_input	input;
	t_gdata	global_data;
	t_ldata	local_data;

	argc--;
	argv++;
	if ((argc < 4) || (argc > 5))
		return (0);
	philo_init_input(&input);
	philo_number_of_philosophers(argv[0], &input);
	philo_init_time(argv[1], &input);
	philo_init_time(argv[2], &input);
	philo_init_time(argv[3], &input);
	if (argc == 5)
		philo_number_of_times_each_philosopher_must_eat(arv[4], &input);
	if (!input.is_valid)
		return (philo_input_is_not_valid(&input));
}
