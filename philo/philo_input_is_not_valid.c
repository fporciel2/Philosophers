/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_input_is_not_valid.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:20:33 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/10 10:30:21 by fporciel         ###   ########.fr       */
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
 * This part of the program logs that the input is not valid.
 */

#include "philo.h"

int	philo_input_is_not_valid(t_input *input)
{
	printf("\n%s\n%s%s%s%s%s%s", NOINPUT, EXECF, NOPF, TTDF, TTEF, TTSF, NTEF);
	if (input)
	{
		if (input->badnop)
			printf("\n* Wrong number of philosophers: %s\n", input->badnop);
		if (input->badthreads)
			printf("\n* Wrong number of philosophers: %s\n", input->badthreads);
		if (input->badttd)
			printf("\n* Wrong time to die: %s\n", input->badttd);
		if (input->badtte)
			printf("\n* Wrong time to eat: %s\n", input->badtte);
		if (input->badtts)
			printf("\n* Wrong time to sleep: %s\n", input->badtts);
		if (input->badnotepme)
			printf("\n* Wrong number of times each philosopher must eat: %s\n",
				input->badnotepme);
	}
	return (0);
}
