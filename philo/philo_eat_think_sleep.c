/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_think_sleep.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:44:27 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/26 12:09:08 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* 'Philosophers' is a simulation that implements a solution to the dining
 * philosophers problem in C. This version is not ready to use and it is not
 * safe to use.
 * This file implements the function that places the activities of eating,
 * thinking and sleeping in alternating mutual exclusion.
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
 * EAT THINK SLEEP
 *
 * The philosophers alternatively eat, think or sleep. While they are eating,
 * they are not thinking nor sleeping; while thinking, they are not eating nor
 * sleeping; and, of course, while sleeping, they are not eating nor thinking.
 */

#include "philo.h"

static int	philo_eat(t_philo *philosophers, t_table *table)
{
	uint64_t	i;

	i = 0;
	while (philosophers[i].is != 0)
	{
		philosophers[i].is_eating = 1;
		table->spaghetti->is_getting_eaten[i] = 1;
		i++;
	}
	i = 0;
	while (philosophers[i].is != 0)
	{
		philosophers[i].is_eating = 0;
		table->spaghetti->is_getting_eaten[i] = 0;
		i++;
	}
	return (1);
}

static int	philo_think(t_philo *philosophers)
{
	uint64_t	i;

	i = 0;
	while (philosophers[i].is != 0)
	{
		philosophers[i].is_thinking = 1;
		i++;
	}
	i = 0;
	while (philosophers[i].is != 0)
	{
		philosophers[i].is_thinking = 0;
		i++;
	}
	return (1);
}

static int	philo_sleep(t_philo *philosophers)
{
	uint64_t	i;

	i = 0;
	while (philosophers[i].is != 0)
	{
		philosophers[i].is_sleeping = 1;
		i++;
	}
	usleep(TIME_TO_SLEEP);
	i = 0;
	while (philosophers[i].is != 0)
	{
		philosophers[i].is_sleeping = 0;
		i++;
	}
	return (1);
}

int	philo_eat_think_sleep(t_philo *philosophers, t_table *table, int time_to)
{
	if (time_to == TIME_TO_EAT)
		return (philo_eat(philosophers, table));
	else if (time_to == TIME_TO_THINK)
		return (philo_think(philosophers));
	else if (time_to == TIME_TO_SLEEP)
		return (philo_sleep(philosophers));
	else
		return (-1);
}
/*TEST FOR EAT_THINK_SLEEP
 * You must test it after 'test_sit_table'.
static int	philo_eat(t_philo *philosophers, t_table *table)
{
	uint64_t	i;

	i = 0;
	printf("\nTESTING EATING\n");
	while (philosophers[i].is != 0)
	{
		philosophers[i].is_eating = 1;
		printf("Philosopher %d is eating: %d.\n", philosophers[i].is,
				philosophers[i].is_eating);
		table->spaghetti->is_getting_eaten[i] = 1;
		printf("Section %lu is getting: %d.\n", i,
			table->spaghetti->is_getting_eaten[i]);
		i++;
	}
	i = 0;
	while (philosophers[i].is != 0)
	{
		philosophers[i].is_eating = 0;
		printf("Philosopher %d is not eating: %d.\n", philosophers[i].is,
				philosophers[i].is_eating);
		table->spaghetti->is_getting_eaten[i] = 0;
		printf("Section %lu is not getting: %d.\n", i,
				table->spaghetti->is_getting_eaten[i]);
		i++;
	}
	return (1);
}

static int	philo_think(t_philo *philosophers)
{
	uint64_t	i;

	i = 0;
	printf("\nTESTING THINKING\n");
	while (philosophers[i].is != 0)
	{
		philosophers[i].is_thinking = 1;
		printf("Philosopher %d is thinking: %d.\n", philosophers[i].is,
				philosophers[i].is_thinking);
		i++;
	}
	i = 0;
	while (philosophers[i].is != 0)
	{
		philosophers[i].is_thinking = 0;
		printf("Philosopher %d is not thinking: %d.\n", philosophers[i].is,
				philosophers[i].is_thinking);
		i++;
	}
	return (1);
}

static int	philo_sleep(t_philo *philosophers)
{
	uint64_t	i;

	i = 0;
	printf("\nTESTING SLEEPING\n");
	while (philosophers[i].is != 0)
	{
		philosophers[i].is_sleeping = 1;
		printf("Philosopher %d is sleeping: %d.\n", philosophers[i].is,
				philosophers[i].is_sleeping);
		i++;
	}
	usleep(TIME_TO_SLEEP);
	i = 0;
	while (philosophers[i].is != 0)
	{
		philosophers[i].is_sleeping = 0;
		printf("Philosopher %d is not sleeping: %d.\n", philosophers[i].is,
				philosophers[i].is_sleeping);
		i++;
	}
	return (1);
}

int	philo_eat_think_sleep(t_philo *philosophers, t_table *table, int time_to)
{
	if (time_to == TIME_TO_EAT)
		return (philo_eat(philosophers, table));
	else if (time_to == TIME_TO_THINK)
		return (philo_think(philosophers));
	else if (time_to == TIME_TO_SLEEP)
		return (philo_sleep(philosophers));
	else
		return (-1);
}

int	main(void)
{
	t_philo	philosophers[11];
	t_table	*table;
	int		i;

	i = 0;
	while (i < 10)
	{
		philosophers[i].is = i + 1;
		printf("Philosopher %d sits at table.\n", philosophers[i].is);
		i++;
	}
	philosophers[i].is = 0;
	printf("END OF PHILOSOPHERS: %d, %d", i, philosophers[i].is);
	printf("\nSTARTING TEST ON PHILOSOPHERS\n");
	table = philo_sit_at_table(philosophers);
	philo_eat_think_sleep(philosophers, table, TIME_TO_EAT);
	philo_eat_think_sleep(philosophers, table, TIME_TO_THINK);
	philo_eat_think_sleep(philosophers, table, TIME_TO_SLEEP);
	philo_clean_table(table);
	return (0);
}*/
