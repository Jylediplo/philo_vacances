/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:53:38 by lefabreg          #+#    #+#             */
/*   Updated: 2024/07/17 15:19:47 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	free_philos(t_philo **philo, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		free(philo[i]->fork->mutex);
		free(philo[i]->fork);
		free(philo[i]);
		i++;
	}
	free(philo);
}

void	free_malloc_fail(t_philo **philos, int nb_philos)
{
	int	i;

	i = 0;
	while (i < nb_philos)
	{
		free(philos[i]);
		i++;
	}
	free(philos);
}
