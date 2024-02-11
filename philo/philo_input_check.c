/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_input_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:34:32 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/11 15:59:20 by fporciel         ###   ########.fr       */
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
 * data type 'uint64_t' and stores it into an array of size 5*sizeof(uint64_t),
 * i.e. the one pointed by 'input'.
 * Then, it returns without returning any value.
 *
 * This concept is extensible. The program does not allow values grater than the
 * ULLONG_MAX as defined in the limits.h header file, but it is possible to
 * imagine a variadic length array and a proper function to manage greater
 * values.
 * However, the program is meant for personal computers, fast executions and
 * limited resouces. Furthermore, its purpose is to show the resolution
 * algorithm for the dining's philosophers problem, not to implement this
 * solution for every possible machine and circumstance of execution.
 *
 * The first thing to do is to include the header file of the program.
 */

#include "philo.h"
/*
 * The function 'philo_atoui64'.
 * It is meant to convert the string into its corresponding integer value using
 * the 'uint64_t' type. The 'uint64_t' type is defined in the 'stdint.h' header.
 * It is used to store the value of the input number in the function.
 * The 'uint64_t' type is a 64-bit unsigned integer type.
 * The function returns the value represented by the string.
 * To do the conversion, it applies an algorithm similar to a power calculator:
 * the first thing done is to initialize the result and an iteration counter to
 * 0, so that the first one can be used to generate the result value by addition
 * and the second one to slide the string "from left to right". 
 * The value of 'len' is decreased by 1 in order to represent the correct
 * position into the decimal representation of the number. The variable 'result'
 * is initialized to 0 to perform subsequent additions. The string is
 * then slided using a while loop, that, for each character, applies the
 * following instructions, if 'len' is not 0:
 * 	- the value of 'pos' is initialized to 1;
 * 	- it is then multiplied for 10 for 'len' times using a 'times' variable
 * 	previously reinitialized to 'len' and decreasing it at each multiplication,
 * 	but only if the current character is different from 48, so that no useless
 * 	multiplications are done;
 * 	- the value of 'digit' is initialized to 'pos'*'the value of the current
 * 	character in the string - 48' if the character is different from 48, else it
 * 	will simply take 0;
 * 	- the value of 'result' is then incremented by 'digit';
 * 	- finally, the value of 'len' is decremented and the value of 'count' is
 * 	incremented.
 * 	This set of instructions proceeds until 'len' reaches 0. Then, the value of
 * 	result is simply updated by increasing it by the value of the current
 * 	character in the string at index 'count'.
 */
static uint64_t	philo_atoui64(char *str, size_t len)
{
	uint64_t	pos;
	uint64_t	digit;
	uint64_t	result;
	uint64_t	count;
	size_t		times;

	count = 0;
	result = 0;
	while (len != 0)
	{
		pos = 1;
		times = len;
		while ((str[count] != 48) && (times-- != 0))
			pos *= 10;
		if (str[count] != 48)
			digit = (str[count] - 48) * pos;
		else
			digit = 0;
		result += digit;
		len--;
		count++;
	}
	return (result + (str[count] - 48));
}

/*
 * The function 'philo_strcheck'.
 * This function is nested into the file and performs a check on the string by
 * ensuring that every character in it is an ASCII digit and that the the length
 * of the string is not greater than 20, that is the value of the number of
 * positions occupied by ULLONG_MAX in its representation in decimal. If this
 * check fails, it returns 0 for the 'uint64_t' type. Otherwise, it returns the
 * output of the atoi-like function for the 'uint64_t' type, passing the pointer
 * to the beginning of the string and the length of the string as parameters to
 * that. The 'size_t' type is defined in the 'stddef.h' header file and is used
 * to store the length of the string.
 */

static uint64_t	philo_strcheck(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != 0)
	{
		if ((str[len] < 48) || (str[len] > 57))
			return (0);
		len++;
	}
	if ((len < 1) || (len > 20))
		return (0);
	return (philo_atoui64(str, (len - 1)));
}
/*
 * This is the main function of the file: 'philo_parse'. As said above, it takes
 * the 'argv' array from the main function and returns an array of size 5*sizeof
 * (uint64_t) that contains the values of the input arguments.
 * The arguments are passed after decreasing the number of arguments by 1 and
 * increasing the pointer by 1, so that the first string in the array is
 * skipped. 
 * For each parameter, the function extracts the string and then parses and
 * convert it into the right integer value, that will be stored in the array.
 * It does so by calling a function that parses the string and calls another
 * atoi-like function for 'uint64_t' type: then, it returns the result that is
 * assigned to the correspondent position in the array.
 * If an error occurs, it sets all the values into the array to 0.
 */

void	philo_parse(int argc, char **argv, uint64_t *input)
{
	input[0] = philo_strcheck(argv[0]);
	input[1] = philo_strcheck(argv[1]);
	input[2] = philo_strcheck(argv[2]);
	input[3] = philo_strcheck(argv[3]);
	if (argc == 5)
		input[4] = philo_strcheck(argv[4]);
	return ;
}
