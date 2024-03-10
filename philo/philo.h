/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:09:32 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/10 17:47:11 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define _DEFAULT_SOURCE
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdbool.h>
# include <limits.h>
# define BADINPUT 1
# define BADALLOC 2
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

typedef struct s_input
{
	int	nb_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_of_times_eat;
}		t_input;

typedef struct s_philo
{
	struct s_table	*table;
	pthread_t		thread;
	int				id;
	pthread_mutex_t	state;
	int				is_alive;
	int				is_eating;
	pthread_mutex_t	lock_meals;
	int				meals;
	int				is_over;
	pthread_mutex_t	last_meal;
	size_t			last_time_eat;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct s_table
{
	t_philo			*philosophers;
	int				nb_of_philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	stdoutput;
	int				is_tragedy;
	int				is_over;
	int				nb_of_times_eat;
	pthread_t		timer;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	uint64_t		start;
}					t_table;

int			philo_isdigit(int c);
long		philo_atoi(const char *str);
int			philo_usleep(uint64_t time);
uint64_t	philo_timestamp(void);
int			philo_init(t_table *table, t_input *input);
void		philo_input_log(t_input *info, int param);
void		philo_table_log(t_table *table);
void		philo_arg_log(t_input *arg, char **argv);
void		philo_start(t_table *table, int nb_of_philo);
void		*philo_life(void *info);
void		philo_free(t_table *table);
void		*philo_timer(void *info);
void		philo_exit_log(int param);
int			philo_eat(t_philo *philo);
uint64_t	philo_log(t_table *table, int id, char *str);
int			philo_input_parse(t_input, *input);
int			philo_table_parse(t_table *table);
void		philo_execute(t_input *test, int flag, t_table *table);

#endif
