/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:48:31 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/12 11:01:26 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* This is the header file for the Philosophers project.
 * Copyright (c) 2024 Federico Porciello
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
 * This is the header file for the Philosophers project. 
 * The ifndef block is an include guard that prevents multiple
 * inclusions of the same header file in the program: this prevents multiple
 * definitions of the same function or variable, which can lead to optimization
 * errors or undefined behaviors.
 */

#ifndef PHILO_H
# define PHILO_H
/*
 * Here are the included headers.
 *
 * TO MANAGE THE INPUT ARGUMENTS are used the stdint.h, limits.h and the
 * stddef.h headers.
 * See the 'philo_input_check.c' file for more details.
 */

# include <stdint.h>
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
/*
 * To properly use a correct number of threads, the macro MAXPHILO is defined at
 * compilation time. See the 'philo_input_check.c' file and the CC variable in
 * the Makefile for more details.
 * Here, we will establish a default value in case of errors.
 */

# ifndef MAXPHILO
#  define MAXPHILO 400
# endif

/*
 * Here are the functions used in the program that need to be included using
 * this header.
 * The first function is 'philo_parse', from the 'philo_input_check.c' file: it
 * provides the parsing of the input arguments and their conversion into an
 * array of integers using the 'uint64_t' type.
 */
void	philo_parse(int argc, char **argv, uint64_t *input);

#endif
