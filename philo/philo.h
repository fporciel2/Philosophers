/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:22:16 by fporciel          #+#    #+#             */
/*   Updated: 2024/02/25 16:02:20 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 * 'Philosophers' is a simulation that implements a solution to the dining
 * philosophers problem in C. This version is not ready to use and it is not
 * safe to use. 
 * This is the header file.
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
 * https://github.com/fporciel2/Philosophers
 *
 * PHILOSOPHERS
 *
 * This is the header file.
 */

#ifndef PHILO_H
# define PHILO_H
# define _DEFAULT_SOURCE
# include <time.h>
# include <sys/types.h>
# include <stdint.h>
# include <string.h>
# include <stddef.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# ifndef MAXPHILOS
#  define MAXPHILOS 400
# endif
# define THINK "is thinking"
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"

typedef struct s_philo
{
	int	is;
}		t_philo;

typedef struct s_bowl
{
	int	test_value;
}		t_bowl;

typedef struct s_table
{
	uint64_t		test_value;
	struct s_philo	*philosopher;
	struct s_bowl	*spaghetti;
	struct s_table	*table;
	struct s_table	*next;
}					t_table;

/* Procedure's prototypes. */
t_table	*philo_sit_at_table(t_philo *philosophers);
/* Cleaning on failure prototypes. */
/* Cleaning on success prototypes. */
t_table	*philo_clean_table(t_table *table);

#endif
