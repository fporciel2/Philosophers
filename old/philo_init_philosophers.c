/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_philosophers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:42:28 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/09 11:49:15 by fporciel         ###   ########.fr       */
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
 * This part of the program initializes the array of philosophers.
 */

#include "philo.h"

static void	philo_assign_last_forks(t_gdata *data, uint64_t i)
{
	if ((i + 1) == (data->number_of_philosophers - 2))
	{
		data->philosophers[i].forks_mutex = data->forks[i].fmutex;
		data->philosophers[i].right_fork = &data->forks[i].fork;
		data->philosophers[i].left_fork = &data->forks[i + 1].fork;
	}
	else if ((i + 1) == (data->number_of_philosophers - 1))
	{
		data->philosophers[i].forks_mutex = data->forks[i].fmutex;
		data->philosophers[i].right_fork = &data->forks[i - 1].fork;
		data->philosophers[i].left_fork = &data->forks[i].fork;
	}
	else
	{
		data->philosophers[i].forks_mutex = data->forks[i].fmutex;
		data->philosophers[i].right_fork = &data->forks[i].fork;
		data->philosophers[i].left_fork = &data->forks[i - 1].fork;
	}
}

static void	philo_assign_forks(t_gdata *data, uint64_t i)
{
	if ((((i + 1) % 2 != 0) && (((i + 1) < (data->number_of_philosophers - 2)))
		&& (data->number_of_philosophers % 2))
		|| (!(data->number_of_philosophers % 2)))
	{
		data->philosophers[i].forks_mutex = data->forks[i].fmutex;
		data->philosophers[i].right_fork = &data->forks[i].fork;
		data->philosophers[i].left_fork = &data->forks[i + 1].fork;
	}
	else if ((((((i + 1) % 2) == 0) && ((i + 1)
			< (data->number_of_philosophers - 2)))
			&& (data->number_of_philosophers % 2))
			|| (!(data->number_of_philosophers % 2)))
	{
		data->philosophers[i].forks_mutex = data->forks[i].fmutex;
		data->philosophers[i].right_fork = &data->forks[i - 1].fork;
		data->philosophers[i].left_fork = &data->forks[i].fork;
	}
	else if (((i + 1) >= (data->number_of_philosophers - 2))
		&& (data->number_of_philosophers % 2))
		philo_assign_last_forks(data, i);
	else
		return ;
}

static void	philo_assign_starting_values(t_gdata *data, uint64_t i,
		t_input *input)
{
	data->philosophers[i].id = i + 1;
	data->philosophers[i].time_to_die = input->time_to_die;
	data->philosophers[i].time_to_eat = input->time_to_eat;
	data->philosophers[i].time_to_sleep = input->time_to_sleep;
	data->philosophers[i].number_of_meals = data->number_of_meals;
	data->philosophers[i].last_meal = &data->timestamps[i].timestamp;
	data->philosophers[i].is_over = &data->is_over;
	data->philosophers[i].stdout_mutex = &data->mutexes->stdout_mutex;
	data->philosophers[i].start_mutex = &data->mutexes->start_mutex;
}

int	philo_init_philosophers(t_input *input, t_gdata *data)
{
	uint64_t	i;

	data->philosophers = (t_philo *)malloc(sizeof(t_philo)
			* (input->number_of_philosophers + 1));
	if (!data->philosophers)
		return (0);
	i = 0;
	while (i < input->number_of_philosophers)
	{
		philo_assign_starting_values(data, i, input);
		philo_assign_forks(data, i);
		data->philosophers[i].timestamp = &data->timestamps[i].timestamp_mutex;
		data->philosophers[i].is_over_mutex = &data->mutexes->is_over_mutex;
		i++;
	}
	data->philosophers[i].id = 0;
	return (1);
}
/* Test Framework.
	i = 0;
	while (data->philosophers[i].id != 0)
	{
		printf("Initialized philosopher %lu\n", data->philosophers[i].id);
		printf("id: %lu\n", data->philosophers[i].id);
		printf("time_to_die: %lu\n", data->philosophers[i].time_to_die);
		printf("time_to_eat: %lu\n", data->philosophers[i].time_to_eat);
		printf("time_to_sleep: %lu\n", data->philosophers[i].time_to_sleep);
		printf("number_of_meals: %lu\n", data->philosophers[i].number_of_meals);
		printf("last_meal add: %p\n", (void *)data->philosophers[i].last_meal);
		printf("\tcheck1: %p\n", (void *)&data->timestamps[i].timestamp);
		printf("\tcheck2: %lu\n", data->timestamps[i].id);
		printf("is_over: %d\n", *data->philosophers[i].is_over);
		printf("stdout_mutex address: %p\n",
				(void *)&data->philosophers[i].stdout_mutex);
		printf("is_over_mutex address: %p\n",
				(void *)&data->philosophers[i].is_over_mutex);
		if (data->philosophers[i].id % 2 == 0)
		{
			printf("right_fork address: %p\n",
					(void *)data->philosophers[i].right_fork);
			printf("left_fork address: %p\n",
					(void *)data->philosophers[i].left_fork);
			printf("\tcheck1: %p\n", (void *)&data->forks[i - 1].fork);
			printf("\tcheck2: %p\n", (void *)&data->forks[i].fork);
			if (data->philosophers[i].right_fork == &data->forks[i - 1].fork)
				printf("\t\tright fork OK\n");
			else
				printf("\t\tright fork NOT OK\n");
			if (data->philosophers[i].left_fork == &data->forks[i].fork)
				printf("\t\tleft fork OK\n");
			else
				printf("\t\tleft fork NOT OK\n");
			printf("\tcheck3(right): %lu\n", data->forks[i - 1].id);
			printf("\tcheck3(left): %lu\n", data->forks[i].id);
		}
		if ((data->philosophers[i].id % 2 != 0)
				&& (data->philosophers[i].id != input->number_of_philosophers))
		{
			printf("right_fork address: %p\n",
					(void *)data->philosophers[i].right_fork);
			printf("left_fork address: %p\n",
					(void *)data->philosophers[i].left_fork);
			printf("\tcheck1: %p\n", (void *)&data->forks[i].fork);
			printf("\tcheck2: %p\n", (void *)&data->forks[i + 1].fork);
			if (data->philosophers[i].right_fork == &data->forks[i].fork)
				printf("\t\tright fork OK\n");
			else
				printf("\t\tright fork NOT OK\n");
			if (data->philosophers[i].left_fork == &data->forks[i + 1].fork)
				printf("\t\tleft fork OK\n");
			else
				printf("\t\tleft fork NOT OK\n");
			printf("\tcheck3(right): %lu\n", data->forks[i].id);
			printf("\tcheck3(left): %lu\n", data->forks[i + 1].id);
		}
		if ((data->philosophers[i].id % 2 != 0)
				&& (data->philosophers[i].id == input->number_of_philosophers))
		{
			printf("right_fork address: %p\n",
					(void *)data->philosophers[i].right_fork);
			printf("left_fork address: %p\n",
					(void *)data->philosophers[i].left_fork);
			printf("third_fork address: %p\n",
					(void *)data->philosophers[i].third_fork);
			printf("\tcheck1: %p\n", (void *)&data->forks[i].fork);
			printf("\tcheck2: %p\n", (void *)&data->forks[i - 2].fork);
			printf("\tcheck3: %p\n", (void *)&data->forks[i - 1].fork);
			if (data->philosophers[i].right_fork == &data->forks[i].fork)
				printf("\t\tright fork OK\n");
			else
				printf("\t\tright fork NOT OK\n");
			if (data->philosophers[i].left_fork == &data->forks[i - 2].fork)
				printf("\t\tleft fork OK\n");
			else
				printf("\t\tleft fork NOT OK\n");
			if (data->philosophers[i].third_fork == &data->forks[i - 1].fork)
				printf("\t\tthird fork OK\n");
			else
				printf("\t\tthird fork NOT OK\n");
			printf("\tcheck4(right): %lu\n", data->forks[i].id);
			printf("\tcheck4(left): %lu\n", data->forks[i - 2].id);
			printf("\tcheck4(third): %lu\n", data->forks[i - 1].id);
		}
		i++;
	}*/
