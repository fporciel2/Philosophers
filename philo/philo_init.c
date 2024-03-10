/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:40:41 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/10 18:57:24 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_set_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_of_philo)
	{
		table->philosophers[i].table = table;
		table->philosophers[i].id = i + 1;
		table->philosophers[i].is_alive = 1;
		table->philosophers[i].is_eating = 0;
		table->philosophers[i].is_over = 0;
		table->philosophers[i].meals = 0;
		table->philosophers[i].time_to_die = table->time_to_die;
		table->philosophers[i].time_to_eat = table->time_to_eat;
		table->philosophers[i].time_to_sleep = table->time_to_sleep;
		pthread_mutex_init(&table->philosophers[i].state, NULL);
		pthread_mutex_init(&table->philosophers[i].lock_meals, NULL);
		pthread_mutex_init(&table->philosophers[i].last_meal, NULL);
		i++;
	}
	return (1);
}

static void	philo_set_forks(t_table *table)
{
	int		i;
	t_philo	*philo;
	int		j;

	j = table->nb_of_philo - 1;
	philo = table->philosophers;
	philo[0].left_fork = &table->forks[0];
	philo[0].right_fork = &table->forks[j];
	i = 1;
	while (i <= table->nb_of_philo)
	{
		philo[i].left_fork = &table->forks[i];
		philo[i].right_fork = &table->forks[i - 1];
		i++;
	}
}

static void	philo_set_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_of_philo)
		pthread_mutex_init(&table->forks[i++], NULL);
	pthread_mutex_init(&table->stdoutput, NULL);
	philo_set_forks(table);
}

static int	philo_free_here(t_table *table)
{
	if (table->forks)
		free(table->forks);
	if (table->philosophers)
		free(table->philosophers);
	return (1);
}

int	philo_init(t_table *table, t_input *input)
{
	table->philosophers = (t_philo *)malloc(sizeof(t_philo)
			* input->nb_of_philo);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* input->nb_of_philo);
	if (!table->philosophers || !table->forks)
		return (philo_free_here(table), 1);
	if (philo_input_parse(input))
		return (philo_free_here(table), 1);
	table->nb_of_philo = input->nb_of_philo;
	table->nb_of_times_eat = input->nb_of_times_eat;
	table->time_to_die = input->time_to_die;
	table->time_to_eat = input->time_to_eat;
	table->time_to_sleep = input->time_to_sleep;
	table->is_tragedy = 0;
	table->is_over = 0;
	philo_set_mutexes(table);
	philo_set_philosophers(table);
	return (0);
}
