/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:56:02 by lefabreg          #+#    #+#             */
/*   Updated: 2024/07/21 03:14:39 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	handle_one_philo(t_philo *philo)
{
	if (philo->nb_philo == 1)
	{
		while (1)
		{
			usleep(100);
			pthread_mutex_lock(philo->all_alive);
			if (!(*philo->alive))
			{
				pthread_mutex_unlock(philo->all_alive);
				return (0);
			}
			pthread_mutex_unlock(philo->all_alive);
		}
	}
	return (1);
}

static void	handle_left_fork(t_philo *philo, int *forks_aquired)
{
	philo->fork->value = 1;
	*forks_aquired += 1;
	lock_print(philo, "has taken a fork");
}

int	take_fork(t_philo *philo)
{
	int	forks_aquired;

	forks_aquired = 0;
	while (1)
	{
		usleep(10);
		pthread_mutex_lock(philo->fork->mutex);
		if (philo->fork->value == 0)
		{
			handle_left_fork(philo, &forks_aquired);
		}
		pthread_mutex_unlock(philo->fork->mutex);
		if (!handle_one_philo(philo))
			return (0);
		pthread_mutex_lock(philo->next->fork->mutex);
		if (philo->next->fork->value == 0)
		{
			philo->next->fork->value = 1;
			forks_aquired += 1;
			lock_print(philo, "has taken a fork");
		}
		pthread_mutex_unlock(philo->next->fork->mutex);
		if (forks_aquired == 2)
			return (1);
	}
}

void	eat(t_philo *philo)
{



	// pthread_mutex_lock(&philo->last_meal_m);
	// long long c = current_timestamp() - philo->last_meal_t;
	// if (c > 2147483647)
	// 	c = 0;
	// if (c + philo->stats->time_to_eat / 1000 > philo->stats->time_to_die / 1000)
	// {
	// 	lock_print(philo, "is deadddd");
	// 	pthread_mutex_lock(philo->all_alive);
	// 	*philo->alive = 0;
	// 	pthread_mutex_unlock(philo->all_alive);
	// }
	// pthread_mutex_unlock(&philo->last_meal_m);
	// lock_print(philo, "is eating");



	custom_usleep(philo->stats->time_to_eat);


	pthread_mutex_lock(&philo->p_meal_eaten);
	philo->meal_eaten += 1;
	pthread_mutex_unlock(&philo->p_meal_eaten);
	
	pthread_mutex_lock(&philo->last_meal_m);

	
	philo->last_meal_t = current_timestamp();
	pthread_mutex_unlock(&philo->last_meal_m);
	pthread_mutex_lock(philo->fork->mutex);
	philo->fork->value = 0;
	pthread_mutex_unlock(philo->fork->mutex);
	pthread_mutex_lock(philo->next->fork->mutex);
	philo->next->fork->value = 0;
	pthread_mutex_unlock(philo->next->fork->mutex);
	lock_print(philo, "is sleeping");
	custom_usleep(philo->stats->time_to_sleep);
	lock_print(philo, "is thinking");
}

void	lock_print(t_philo *philo, char *message)
{
	
	pthread_mutex_lock(philo->print);
	pthread_mutex_lock(philo->all_alive);
	pthread_mutex_lock(philo->p_ate_all_meal);

	
	if (*philo->alive && !(*philo->ate_all_meal))
	{
		pthread_mutex_lock(&philo->time);
		printf("%lld %d %s\n", current_timestamp() - philo->start_time,
			philo->rank, message);
		pthread_mutex_unlock(&philo->time);
	}
	pthread_mutex_unlock(philo->all_alive);
	pthread_mutex_unlock(philo->p_ate_all_meal);
	pthread_mutex_unlock(philo->print);
}
