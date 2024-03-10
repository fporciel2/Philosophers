/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:34:17 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/10 18:40:08 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_exit_log(int param)
{
	(void)param;
	printf("The number of philosophers will go crazy like everybody\n");
	return ;
}

void	philo_free(t_table *table)
{
	free(table->forks);
	free(table->philosophers);
	return ;
}

void	philo_execute(t_input *input, int param, t_table *table)
{
	philo_input_log(input, param);
	philo_init(table, input);
	philo_table_log(table);
	philo_free(table);
}
