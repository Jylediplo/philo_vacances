/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:54:04 by lefabreg          #+#    #+#             */
/*   Updated: 2024/07/17 15:44:46 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	destroy_forks(t_philo **philos, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_destroy(&philos[i]->death);
		pthread_mutex_destroy(&philos[i]->time);
		pthread_mutex_destroy(&philos[i]->last_meal_m);
		pthread_mutex_destroy(&philos[i]->p_meal_eaten);
		pthread_mutex_destroy(philos[i]->fork->mutex);
		i++;
	}
}

void	destroy_mutex(t_mutex *mutex)
{
	pthread_mutex_destroy(mutex->mutex_print);
	pthread_mutex_destroy(mutex->dead);
	pthread_mutex_destroy(mutex->p_eat);
	pthread_mutex_destroy(mutex->p_start);
	pthread_mutex_destroy(mutex->wait_philo);
}
