/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:46:40 by lefabreg          #+#    #+#             */
/*   Updated: 2024/08/02 23:56:22 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_stats
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_to_eat;
	int				meal_eaten;
	int				nb_params;

}					t_stats;

typedef struct s_fork
{
	int				value;
	pthread_mutex_t	*mutex;

}					t_fork;

typedef struct s_mutex
{
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*p_eat;
	pthread_mutex_t	*p_start;
	pthread_mutex_t	*wait_philo;
	int				all_alive;
	int				all_eat;
	int				started;

}					t_mutex;

typedef struct s_philo
{
	int				rank;
	long long		start_time;
	long long		last_meal_t;
	long long		current_time;
	pthread_mutex_t	*print;
	pthread_mutex_t	*all_alive;
	pthread_mutex_t	*p_ate_all_meal;
	pthread_mutex_t	*p_start;
	pthread_mutex_t	p_meal_eaten;
	pthread_mutex_t	death;
	pthread_mutex_t	time;
	pthread_mutex_t	time_1;
	int				time_ready;
	pthread_mutex_t	last_meal_m;
	pthread_mutex_t	*m_wait;
	int				meal_eaten;
	int				start;
	int				*alive;
	int				*ate_all_meal;
	int				*started;
	t_stats			*stats;
	pthread_t		thread;
	struct s_philo	*next;
	struct s_philo	*previous;
	int				nb_philo;
	int				ate_all;
	int				ready;
	t_fork			*fork;
}					t_philo;

void				init_philos(t_philo **all_philos, int nb_philo,
						t_stats *stats);
t_philo				**create_philos(int nb_philos);
char				*init_forks(t_philo **philos, int nb_philo);
void				free_philos(t_philo **philo, int nb_philo);
int					take_fork(t_philo *philo);
void				eat(t_philo *philo);
void				lock_print(t_philo *philo, char *message);
long long			current_timestamp(void);
void				custom_usleep(int time_sleep, t_philo *philo);
void				waiting_for_philo_ready(int nb_philo, t_philo **philo);
int					ft_atol(const char *str);
void				init_time(int nb_philo, t_philo **philo);
void				check_if_dead(t_philo **philo, int i,
						long long *elapsed_time, int *is_dead);
void				check_meals(t_philo **philo, int i, int nb_philo,
						int *philos_that_ate);
void				routine(t_philo *philo);
int					wait_all_philos_to_start(t_philo *philo);
void				destroy_forks(t_philo **philos, int nb_philo);
void				free_malloc_fail(t_philo **philos, int nb_philos);
int					initialise_mutex(t_mutex *mutex);
void				free_mutex(t_mutex *mutex);
void				initialise_each_philo(t_mutex *mutex, t_philo **philo,
						int nb_philo);
int					create_and_join(t_philo **philo, int nb_philo);
void				*handler(void *philo_thread);
void				monitoring(t_philo **philo, int nb_philo);
int					manage_args(t_stats *stats, int argc, char **argv);
void				manage_state(t_philo *philo);
void				init_stats(t_stats *stats, char **argv);
void				destroy_mutex(t_mutex *mutex);
int					clean_code(t_philo **philo, int i);
#endif