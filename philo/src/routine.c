/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:44:00 by lefabreg          #+#    #+#             */
/*   Updated: 2024/08/02 23:47:49 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	routine(t_philo *philo)
{
	while (1)
	{
		if (!take_fork(philo))
			break ;
		eat(philo);
		pthread_mutex_lock(philo->all_alive);
		if (!(*philo->alive))
		{
			pthread_mutex_unlock(philo->all_alive);
			break ;
		}
		pthread_mutex_unlock(philo->all_alive);
		pthread_mutex_lock(philo->p_ate_all_meal);
		if (*philo->ate_all_meal)
		{
			pthread_mutex_unlock(philo->p_ate_all_meal);
			break ;
		}
		pthread_mutex_unlock(philo->p_ate_all_meal);
	}
}

int	wait_all_philos_to_start(t_philo *philo)
{
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(philo->p_start);
		pthread_mutex_lock(philo->all_alive);
		if (*philo->started == philo->nb_philo || *philo->alive == 0)
		{
			pthread_mutex_unlock(philo->p_start);
			pthread_mutex_unlock(philo->all_alive);
			return (0);
		}
		pthread_mutex_unlock(philo->p_start);
		pthread_mutex_unlock(philo->all_alive);
		return (1);
	}
}
