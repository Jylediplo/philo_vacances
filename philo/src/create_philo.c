/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:43:22 by lefabreg          #+#    #+#             */
/*   Updated: 2024/08/03 00:15:16 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	manage_args(t_stats *stats, int argc, char **argv)
{
	if (argc == 5)
	{
		init_stats(stats, argv);
		stats->nb_params = 4;
		if (ft_atol(argv[4]) < 0 || ft_atol(argv[3]) < 0
			|| ft_atol(argv[2]) < 0)
			return (write(2, "Error passing arguments\n", 24), 1);
	}
	else if (argc == 6)
	{
		init_stats(stats, argv);
		stats->nb_params = 5;
		if (ft_atol(argv[5]) < 0)
			return (write(2, "Error wrong nb of meals\n", 24), 1);
		stats->meal_to_eat = ft_atol(argv[5]);
	}
	else
	{
		write(2, "please enter 4 or 5 arguments !\n", 32);
		return (1);
	}
	return (0);
}

t_philo	**create_philos(int nb_philos)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo *) * nb_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (free_malloc_fail(philos, nb_philos), NULL);
		i++;
	}
	return (philos);
}
