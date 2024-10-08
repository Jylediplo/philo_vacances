/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:58:09 by lefabreg          #+#    #+#             */
/*   Updated: 2024/08/02 17:30:43 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

long long	current_timestamp(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000 + te.tv_usec / 1000;
	return (milliseconds);
}

void	custom_usleep(int time_sleep, t_philo *philo)
{
	long long	start;

	start = current_timestamp();
	while (current_timestamp() - start < time_sleep / 1000)
	{
		pthread_mutex_lock(philo->all_alive);
		if (*philo->alive == 0)
		{
			pthread_mutex_unlock(philo->all_alive);
			break ;
		}
		pthread_mutex_unlock(philo->all_alive);
		usleep(150);
	}
}
