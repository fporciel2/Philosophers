/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:49:23 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/10 18:12:18 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_take_forks(t_philo *philo, int param)
{
	if (param == 1)
	{
		philo_log(philo->table, philo->id, FORK);
		philo_usleep(philo->time_to_die);
		return (1);
	}
	if (!philo_table_parse(philo->table) && philo->is_alive)
	{
		if (philo_table_parse(philo->table) || !philo->is_alive)
			return (1);
		pthread_mutex_lock(philo->right_fork);
		if (philo_table_parse(philo->table) || !philo->is_alive)
			return (1);
		philo_log(philo->table, philo->id, FORK);
		if (philo_table_parse(philo->table) || !philo->is_alive)
			return (1);
		pthread_mutex_lock(philo->left_fork);
		if (philo_table_parse(philo->table) || !philo->is_alive)
			return (1);
		philo_log(philo->table, philo->id, FORK);
		return (0);
	}
	return (1);
}

static int	philo_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->state);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->state);
	if (philo_table_parse(philo->table))
		return (1);
	else
		return (0);
}

static void	philo_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal);
	philo->last_time_eat = philo_timestamp() + philo->time_to_die;
	pthread_mutex_unlock(&philo->last_meal);
	pthread_mutex_lock(&philo->lock_meals);
	philo->meals++;
	pthread_mutex_unlock(&philo->lock_meals);
}

static void	philo_lock_life(t_philo *philo)
{
	pthread_mutex_lock(&philo->state);
	philo->is_alive = 1;
	philo->is_eating = 1;
	pthread_mutex_unlock(&philo->state);
}

int	philo_eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (table->nb_of_philo == 1)
		return (philo_take_forks(philo, 1));
	else
	{
		if (!philo_table_parse(philo->table) && philo->is_alive == 1)
		{
			if (philo_take_forks(philo, 0))
				return (1);
			if (!philo_table_parse(philo->table))
				philo_log(philo->table, philo->id, EAT);
			philo_lock_life(philo);
			philo_last_meal(philo);
			philo_usleep(philo->time_to_eat);
			return (philo_release_forks(philo));
		}
	}
	return (1);
}
