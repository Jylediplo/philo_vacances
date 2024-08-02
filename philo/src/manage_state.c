/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:36:19 by lefabreg          #+#    #+#             */
/*   Updated: 2024/08/03 00:18:20 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	manage_state(t_philo *philo)
{
	long long	c;

	pthread_mutex_lock(&philo->last_meal_m);
	c = current_timestamp() - philo->last_meal_t;
	if (c > 2147483647)
		c = 0;
	if ((c + philo->stats->time_to_eat / 1000 > philo->stats->time_to_die
			/ 1000) && (philo->stats->time_to_die
			/ 1000 > philo->stats->time_to_eat / 1000))
	{
		lock_print(philo, "is dead");
		pthread_mutex_lock(philo->all_alive);
		*philo->alive = 0;
		pthread_mutex_unlock(philo->all_alive);
	}
}
