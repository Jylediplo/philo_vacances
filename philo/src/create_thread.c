/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:52:59 by lefabreg          #+#    #+#             */
/*   Updated: 2024/08/02 23:57:03 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	initialise_mutex(t_mutex *mutex)
{
	mutex->mutex_print = malloc(sizeof(pthread_mutex_t));
	if (!mutex->mutex_print)
		return (1);
	mutex->dead = malloc(sizeof(pthread_mutex_t));
	if (!mutex->dead)
		return (free(mutex->mutex_print), 1);
	mutex->p_eat = malloc(sizeof(pthread_mutex_t));
	if (!mutex->p_eat)
		return (free(mutex->mutex_print), free(mutex->dead), 1);
	mutex->p_start = malloc(sizeof(pthread_mutex_t));
	if (!mutex->p_start)
		return (free(mutex->mutex_print), free(mutex->dead), free(mutex->p_eat),
			1);
	mutex->wait_philo = malloc(sizeof(pthread_mutex_t));
	if (!mutex->wait_philo)
		return (free(mutex->mutex_print), free(mutex->dead), free(mutex->p_eat),
			free(mutex->p_start), 1);
	pthread_mutex_init(mutex->mutex_print, NULL);
	pthread_mutex_init(mutex->dead, NULL);
	pthread_mutex_init(mutex->p_eat, NULL);
	pthread_mutex_init(mutex->p_start, NULL);
	pthread_mutex_init(mutex->wait_philo, NULL);
	return (0);
}

void	initialise_each_philo(t_mutex *mutex, t_philo **philo, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		philo[i]->alive = &mutex->all_alive;
		philo[i]->ate_all_meal = &mutex->all_eat;
		philo[i]->m_wait = mutex->wait_philo;
		philo[i]->start_time = 0;
		philo[i]->print = mutex->mutex_print;
		philo[i]->all_alive = mutex->dead;
		philo[i]->p_ate_all_meal = mutex->p_eat;
		philo[i]->p_start = mutex->p_start;
		philo[i]->start = 0;
		philo[i]->started = &mutex->started;
		i++;
	}
}

void	free_mutex(t_mutex *mutex)
{
	free(mutex->wait_philo);
	free(mutex->mutex_print);
	free(mutex->dead);
	free(mutex->p_eat);
	free(mutex->p_start);
}

int	create_and_join(t_philo **philo, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(&philo[i]->thread, NULL, handler,
				(void *)philo[i]) != 0)
			return (clean_code(philo, i));
		i++;
	}
	i = 0;
	monitoring(philo, nb_philo);
	while (i < nb_philo)
	{
		pthread_join(philo[i]->thread, NULL);
		i++;
	}
	return (0);
}
int	clean_code(t_philo **philo, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_lock(philo[j]->all_alive);
		*philo[j]->alive = 0;
		pthread_mutex_unlock(philo[j]->all_alive);
		pthread_join(philo[j]->thread, NULL);
		j++;
	}
	return (1);
}
