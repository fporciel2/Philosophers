/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:15:06 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/10 18:33:39 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	philo_log(t_table *table, int id, char *str)
{
	uint64_t	time;

	time = philo_timestamp() - table->start;
	pthread_mutex_lock(&table->stdoutput);
	printf("%lu %d %s\n", time, id, str);
	pthread_mutex_unlock(&table->stdoutput);
	return (philo_timestamp());
}

int	philo_input_parse(t_input *input)
{
	if (input->nb_of_philo <= 0)
		return (printf("Number of philosophers must be positive\n"), 0);
	if (input->time_to_die <= 0)
		return (printf("Time to die must be positive\n"), 0);
	if (input->time_to_eat <= 0)
		return (printf("Time to eat must be positive\n"), 0);
	if (input->time_to_sleep <= 0)
		return (printf("Time to sleep must be positive\n"), 0);
	if (input->nb_of_times_eat < 0)
		return (printf("Number of times to eat must be positive\n"), 0);
	return (0);
}

void	philo_table_log(t_table *table)
{
	int	i;

	i = 0;
	printf("\n\nBEGINNING\n\n");
	printf("Number of philosophers: %d\n", table->nb_of_philo);
	while (i < table->nb_of_philo)
	{
		printf("Philosopher %d\n", table->philosophers[i].id);
		printf("Meals eaten: %d\n", table->philosophers[i].meals);
		printf("Dies in %zu millisecons\n", table->philosophers[i].time_to_die);
		printf("Eats in %zu millisecons\n", table->philosophers[i].time_to_eat);
		printf("Sleeps in %zu millisecons\n",
				table->philosophers[i].time_to_sleep);
		i++;
	}
	philo_start(table, table->nb_of_philo);
}

void	philo_input_log(t_philo *philo, int param)
{
	if (!philo_input_parse(philo))
	{
		printf("Number of philosophers: %d\n", philo->nb_of_philo);
		printf("Time to die: %d\n", philo->time_to_die);
		printf("Time to eat: %d\n", philo->time_to_eat);
		printf("Time to sleep: %d\n", philo->time_to_sleep);
		if (param == 1)
			printf("Number of times to eat: %d\n", philo->nb_of_times_eat);
		else
			printf("Number of times to eat: -\n");
	}
	return ;
}
