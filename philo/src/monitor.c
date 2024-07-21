/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:02:52 by lefabreg          #+#    #+#             */
/*   Updated: 2024/07/17 15:21:49 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	waiting_for_philo_ready(int nb_philo, t_philo **philo)
{
	int	i;
	int	count_philo_ready;

	count_philo_ready = 0;
	i = -1;
	while (++i < nb_philo)
	{
		usleep(100);
		while (count_philo_ready != nb_philo)
		{
			pthread_mutex_lock(philo[i]->m_wait);
			if (philo[i]->start == 1 && philo[i]->ready == 0)
			{
				pthread_mutex_lock(philo[i]->p_start);
				usleep(100);
				*philo[i]->started += 1;
				pthread_mutex_unlock(philo[i]->p_start);
				philo[i]->ready = 1;
				count_philo_ready += 1;
				pthread_mutex_unlock(philo[i]->m_wait);
				break ;
			}
			pthread_mutex_unlock(philo[i]->m_wait);
		}
	}
}

void	init_time(int nb_philo, t_philo **philo)
{
	int			j;
	long long	general_time;

	j = 0;
	general_time = current_timestamp();
	while (j < nb_philo)
	{
		pthread_mutex_lock(&philo[j]->time);
		philo[j]->start_time = general_time;
		pthread_mutex_unlock(&philo[j]->time);
		pthread_mutex_lock(&philo[j]->time_1);
		philo[j]->time_ready = 1;
		pthread_mutex_unlock(&philo[j]->time_1);
		j++;
	}
}

void	check_if_dead(t_philo **philo, int i, long long *elapsed_time,
		int *is_dead)
{
	pthread_mutex_lock(&philo[i]->last_meal_m);
	if (philo[i]->last_meal_t == 0)
	{
		pthread_mutex_lock(&philo[i]->time);
		*elapsed_time = current_timestamp() - philo[i]->start_time;
		pthread_mutex_unlock(&philo[i]->time);
	}
	else
		*elapsed_time = current_timestamp() - philo[i]->last_meal_t;
	pthread_mutex_unlock(&philo[i]->last_meal_m);
	if (*elapsed_time > (philo[i]->stats->time_to_die / 1000))
	{
		lock_print(philo[i], "died");
		pthread_mutex_lock(philo[i]->all_alive);
		*philo[i]->alive = 0;
		pthread_mutex_unlock(philo[i]->all_alive);
		*is_dead = 1;
		return ;
	}
}

void	check_meals(t_philo **philo, int i, int nb_philo, int *philos_that_ate)
{
	pthread_mutex_lock(&philo[i]->p_meal_eaten);
	if (philo[i]->meal_eaten == philo[i]->stats->meal_to_eat)
	{
		if (philo[i]->ate_all == 0)
		{
			philo[i]->ate_all = 1;
			*philos_that_ate += 1;
		}
	}
	pthread_mutex_unlock(&philo[i]->p_meal_eaten);
	if (*philos_that_ate == nb_philo && philo[i]->stats->nb_params == 5)
	{
		pthread_mutex_lock(philo[i]->p_ate_all_meal);
		*philo[i]->ate_all_meal = 1;
		pthread_mutex_unlock(philo[i]->p_ate_all_meal);
		return ;
	}
}
