/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:45:14 by lefabreg          #+#    #+#             */
/*   Updated: 2024/07/17 16:14:50 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	init_if_not_first_philo(t_philo **all_philos, int nb_philo, int i)
{
	all_philos[i]->previous = all_philos[i - 1];
	if (i != nb_philo - 1)
		all_philos[i]->next = all_philos[i + 1];
	else
		all_philos[i]->next = all_philos[0];
}

void	init_philos(t_philo **all_philos, int nb_philo, t_stats *stats)
{
	int		i;

	i = 0;
	while (i < nb_philo)
	{
		all_philos[i]->nb_philo = nb_philo;
		all_philos[i]->rank = i + 1;
		all_philos[i]->ate_all = 0;
		all_philos[i]->start = 0;
		all_philos[i]->started = 0;
		all_philos[i]->ready = 0;
		all_philos[i]->stats = stats;
		if (i == 0 && nb_philo != 1)
		{
			all_philos[i]->previous = all_philos[nb_philo - 1];
			all_philos[i]->next = all_philos[i + 1];
		}
		else if (nb_philo != 1)
		{
			init_if_not_first_philo(all_philos, nb_philo, i);
		}
		i++;
	}
}

static void	free_malloc_fail_fork(t_philo **philos, int nb_philo, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(philos[i]->fork->mutex);
		free(philos[i]->fork);
		i++;
	}
	free_malloc_fail(philos, nb_philo);
}

static void	free_malloc_fail_fork_mutex(t_philo **philos, int nb_philo,
		int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(philos[i]->fork->mutex);
		free(philos[i]->fork);
		i++;
	}
	free(philos[i]->fork->mutex);
	free(philos[i]->fork);
	free_malloc_fail(philos, nb_philo);
}

char	*init_forks(t_philo **philos, int nb_philo)
{
	int	i;

	i = -1;
	while (++i < nb_philo)
	{
		pthread_mutex_init(&(philos[i]->death), NULL);
		pthread_mutex_init(&(philos[i]->time), NULL);
		pthread_mutex_init(&(philos[i]->time_1), NULL);
		pthread_mutex_init(&(philos[i]->p_meal_eaten), NULL);
		pthread_mutex_init(&(philos[i]->last_meal_m), NULL);
		philos[i]->fork = malloc(sizeof(t_fork));
		if (!philos[i]->fork)
			return (free_malloc_fail_fork(philos, nb_philo, i), NULL);
		philos[i]->fork->mutex = malloc(sizeof(pthread_mutex_t));
		if (!philos[i]->fork->mutex)
			return (free_malloc_fail_fork_mutex(philos, nb_philo, i), NULL);
		pthread_mutex_init(philos[i]->fork->mutex, NULL);
		philos[i]->fork->value = 0;
		philos[i]->meal_eaten = 0;
		philos[i]->last_meal_t = 0;
		philos[i]->current_time = 0;
		philos[i]->last_meal_t = 0;
		philos[i]->time_ready = 0;
	}
	return ("ok");
}
