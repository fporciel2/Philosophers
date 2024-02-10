/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_input_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:34:32 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/10 17:29:30 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* This file is part of the Philosophers project. Its purpose is to check the
 * validity of the input given by the user.
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
 * The function blocks in this file are meant to check the validity of the input
 * given by the user. There are not theoretical restriction to the number of
 * philosophers, i.e. threads, allowed to be created, nor to the time to die,
 * the time to eat, the time to sleep and the number of times each philosopher
 * must eat. However, there are technical limitations given by the computer and
 * system architecture. This program is written with Debian GNU/Linux in mind,
 * but it can be easily adapted to other systems. In Debian GNU/Linux, the
 * maximum number of threads allowed is typically defined at the path:
 * '/proc/sys/kernel/threads-max' (this can be wrong). Due to the technical
 * limitations of this program that is, the fact that the standard C language
 * functions used do not allow the input value to be compared with the thread
 * limit per process defined by the operating system, I will define the macro
 * MAXPHILO at compilation time by automating the threads-max's retrieving using
 * the Makefile: so, the call option will have 'gcc -DMAXPHILO=$(MAXTHREADS)',
 * where MAXTHREADS will be defined as
 * 'MAXTHREADS := $(shell cat /proc/sys/kernel/threads-max)'. This check
 * functions will also reduce this value according to the number of auxiliar
 * threads created by the program.
 * Since the Philosophers program is a theoretical simulation, no other
 * limitations will be imposed on the input values, apart from positivity,
 * because a negative time value, a negative number of philosophers, or a
 * negative number of times each philosopher must eat, would be meaningless. 
 *
 * Now, the number of philosophers, i.e. threads, is the first parameter to
 * check. Then, the time to die, the time to eat, the time to sleep and the
 * number of times each philosopher must eat are the next four parameters. The
 * program will also check that the number of arguments is not less than 4, nor
 * grater than 5, because the number of times each philosopher must eat is an
 * optional value.
 *
 * After checking the validity of each input, if the program finds no errors, it
 * converts the alphanumeric code into an integer value using the stdint.h's
 * data type 'uint64_t' and stores it into an array of size 5*sizeof(uint64_t).
 * Then, it returns the array.
 *
 * This concept is extensible. The program does not allow values grater than the
 * UINTMAX_MAX as defined in the limits.h header file, but it is possible to
 * imagine a variadic length array and a proper function to manage greater
 * values.
 * However, the program is meant to adhere to the C17 standard and to the 42
 * Norm: so, no VLAs are used and the use of realloc to should be too
 * inefficient. Furthermore, this program is meant for personal computers, so
 * the number of threads could not be so high, and increasing the timescales so
 * much would be unfair to those observing the simulation, who probably have
 * other things to do, such as living their lives happily.
 *
 * The first thing to do is to include the header file of the program.
 */

#include "philo.h"
/*
 * This is the main function of the file: 'philo_parse'.
 */
