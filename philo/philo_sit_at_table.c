/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sit_at_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:29:54 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/26 11:18:34 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* 'Philosophers' is a simulation that implements a solution to the dining
 * philosophers problem in C. This version is not ready to use and it is not
 * safe to use.
 * This is the implementation of the table with spaghetti.
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
 * SIT AT TABLE
 *
 * One or more philosophers sit at a round table. There is a large bowl of
 * spaghetti in the middle of the table.
 */

#include "philo.h"

static uint64_t	philo_count_philosophers(t_philo *philosophers)
{
	uint64_t	i;

	i = 0;
	if (philosophers)
	{
		while (philosophers[i].is != 0)
			i++;
	}
	return (i);
}

static t_table	*philo_create_table(t_table *table, uint64_t number)
{
	uint64_t	i;

	i = 0;
	table = (t_table *)malloc(sizeof(t_table) * number);
	if (table == NULL)
		return (NULL);
	if (number != 1)
	{
		while (i < (number - 1))
		{
			table[i].table = table;
			table[i].next = &table[i + 1];
			i++;
		}
	}
	table[i].table = table;
	table[i].next = &table[0];
	return (table);
}

static t_bowl	*philo_create_bowl(uint64_t number)
{
	t_bowl		*spaghetti;
	uint64_t	i;

	spaghetti = (t_bowl *)malloc(sizeof(t_bowl));
	if (spaghetti == NULL)
		return (NULL);
	i = 0;
	spaghetti->is_getting_eaten = (int *)malloc(sizeof(int) * (number + 1));
	if (spaghetti->is_getting_eaten == NULL)
		return (free(spaghetti), NULL);
	while (i < number)
	{
		spaghetti->is_getting_eaten[i] = 0;
		i++;
	}
	spaghetti->is_getting_eaten[number] = -1;
	return (spaghetti);
}

t_table	*philo_sit_at_table(t_philo *philosophers)
{
	t_table		*table;
	t_bowl		*spaghetti;
	uint64_t	number_of_philosophers;
	uint64_t	i;

	number_of_philosophers = philo_count_philosophers(philosophers);
	if (number_of_philosophers == 0)
		return (NULL);
	table = philo_create_table(NULL, number_of_philosophers);
	if (table == NULL)
		return (NULL);
	spaghetti = philo_create_bowl(number_of_philosophers);
	if (spaghetti == NULL)
		return (free(table), NULL);
	i = 0;
	while (i < number_of_philosophers)
	{
		table[i].philosopher = &philosophers[i];
		table[i].spaghetti = spaghetti;
		i++;
	}
	return (table);
}
/* TEST_PHILO_SIT_AT_TABLE
 *
 * To test the algorithm:
 *
 * 'gcc -std=c17 -pedantic-errors -Wall -Wextra -Werror -I$(pwd) philo.h
 * philo_sit_at_table.c philo_clean_table.c -lc -o test_philo_sit_at_table'
 *
 * To test the memory:
 *
 * 'valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes
 * --show-reachable=yes -show-error-list=yes -s -v ./test_philo_sit_at_table'
 *
 *  The test is passed.
 *
 ***************************************************************************
static uint64_t	philo_count_philosophers(t_philo *philosophers)
{
	uint64_t	i;

	i = 0;
	if (philosophers)
	{
		while (philosophers[i].is != 0)
			i++;
	}
	return (i);
}

static t_table	*philo_create_table(t_table *table, uint64_t number)
{
	uint64_t	i;

	i = 0;
	table = (t_table *)malloc(sizeof(t_table) * number);
	if (table == NULL)
		return (NULL);
	printf("Table created.\n");
	if (number != 1)
	{
		while (i < (number - 1))
		{
			printf("Index of table: %lu.\n", i);
			table[i].test_value = i + 1;
			printf("Test value for table %lu: %lu.\n", i, table[i].test_value);
			table[i].table = table;
			printf("Head of table %lu: %lu.\n", table[i].test_value,
					table[i].table->test_value);
			table[i].next = &table[i + 1];
			if (i > 0)
				printf("Next of table %lu: %lu.\n", table[i - 1].test_value,
						table[i - 1].next->test_value);
			i++;
		}
	}
	table[i].table = table;
	table[i].test_value = i + 1;
	printf("Test value for table %lu: %lu.\n", i, table[i].test_value);
	printf("Head of table %lu: %lu.\n", table[i].test_value,
			table[i].table->test_value);
	table[i].next = &table[0];
	printf("Next of table %lu: %lu.\n", table[i].test_value,
			table[i].next->test_value);
	return (table);
}

t_table	*philo_sit_at_table(t_philo *philosophers)
{
	t_table		*table;
	t_bowl		*spaghetti;
	uint64_t	number_of_philosophers;
	uint64_t	i;

	number_of_philosophers = philo_count_philosophers(philosophers);
	if (number_of_philosophers == 0)
		return (NULL);
	printf("Number of philosophers: %lu\n", number_of_philosophers);
	table = philo_create_table(NULL, number_of_philosophers);
	if (table == NULL)
		return (NULL);
	printf("Table created.\n");
	spaghetti = (t_bowl *)malloc(sizeof(t_bowl));
	if (spaghetti == NULL)
		return (free(table), NULL);
	spaghetti->test_value = 1;
	printf("Test value for spaghetti %d.\n", spaghetti->test_value);
	i = 0;
	while (i < number_of_philosophers)
	{
		printf("Index of table: %lu.\n", i);
		table[i].philosopher = &philosophers[i];
		printf("Philosopher %d sits at table.\n", table[i].philosopher->is);
		table[i].spaghetti = spaghetti;
		printf("Spaghetti assigned: %d.\n", table[i].spaghetti->test_value);
		i++;
	}
	return (table);
}

int	main(void)
{
	t_philo		philosophers[10];
	t_philo		philosophers1[11];
	t_philo		philosophers3[1];
	t_philo		philosophers4[2];
	t_philo		philosophers5[3];
	t_table		*table;
	uint64_t	i;

	i = 0;
	while (i < 9)
	{
		philosophers[i].is = (i + 1);
		i++;
	}
	philosophers[i].is = 0;
	printf("\nSTARTING TEST ON PHILOSOPHERS 0\n");
	table = philo_sit_at_table(philosophers);
	if (table == NULL)
		return (printf("Failure in allocating table\n"));
	philo_clean_table(table);
	i = 0;
	while (i < 10)
	{
		philosophers1[i].is = (i + 1);
		i++;
	}
	philosophers1[i].is = 0;
	printf("\nSTARTING TEST ON PHILOSOPHERS 1\n");
	table = philo_sit_at_table(philosophers1);
	if (table == NULL)
		return (printf("Failure in allocating table\n"));
	philo_clean_table(table);
	i = 0;
	while (i < 1)
	{
		philosophers3[i].is = (i + 1);
		i++;
	}
	philosophers3[i].is = 0;
	printf("\nSTARTING TEST ON PHILOSOPHERS 3\n");
	table = philo_sit_at_table(philosophers3);
	if (table == NULL)
		return (printf("Failure in allocating table\n"));
	philo_clean_table(table);
	i = 0;
	while (i < 2)
	{
		philosophers4[i].is = (i + 1);
		i++;
	}
	philosophers4[i].is = 0;
	printf("\nSTARTING TEST ON PHILOSOPHERS 4\n");
	table = philo_sit_at_table(philosophers4);
	if (table == NULL)
		return (printf("Failure in allocating table\n"));
	philo_clean_table(table);
	i = 0;
	while (i < 3)
	{
		philosophers5[i].is = (i + 1);
		i++;
	}
	philosophers5[i].is = 0;
	printf("\nSTARTING TEST ON PHILOSOPHERS 5\n");
	table = philo_sit_at_table(philosophers5);
	if (table == NULL)
		return (printf("Failure in allocating table\n"));
	philo_clean_table(table);
	printf("\nTEST ON PHILOSOPHERS PASSED\n");
	return (0);
}*/
