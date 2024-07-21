/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:41:52 by lefabreg          #+#    #+#             */
/*   Updated: 2024/07/21 03:21:21 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	*handler(void *philo_thread)
{
	t_philo		*philo;
	int			i;

	i = 0;
	philo = (t_philo *)philo_thread;
	pthread_mutex_lock(philo->m_wait);
	philo->start = 1;
	pthread_mutex_unlock(philo->m_wait);
	wait_all_philos_to_start(philo);
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(&philo->time_1);
		if (philo->time_ready)
		{
			pthread_mutex_unlock(&philo->time_1);
			break ;
		}
		pthread_mutex_unlock(&philo->time_1);
	}
	lock_print(philo, "is thinking");
	if (philo->rank % 2 == 0)
		custom_usleep(philo->stats->time_to_eat);
	return (routine(philo), NULL);
}

void	monitoring(t_philo **philo, int nb_philo)
{
	int			i;
	int			is_dead;
	long long	elapsed_time;
	int			philos_that_ate;

	i = 0;
	is_dead = 0;
	philos_that_ate = 0;
	waiting_for_philo_ready(nb_philo, philo);
	init_time(nb_philo, philo);
	while (!is_dead)
	{
		i = 0;
		while (i < nb_philo)
		{
			usleep(600);
			check_if_dead(philo, i, &elapsed_time, &is_dead);
			check_meals(philo, i, nb_philo, &philos_that_ate);
			i++;
		}
	}
}

void	create_thread(t_philo **philo, int nb_philo)
{
	t_mutex	mutex;

	mutex.all_alive = 1;
	mutex.all_eat = 0;
	mutex.started = 0;
	if (initialise_mutex(&mutex))
		return (printf("Error malloc : initialising philos"), (void)0);
	initialise_each_philo(&mutex, philo, nb_philo);
	create_and_join(philo, nb_philo);
	destroy_mutex(&mutex);
	destroy_forks(philo, nb_philo);
	free_mutex(&mutex);
	return ;
}

void	init_stats(t_stats *stats, char **argv)
{
	stats->nb_philo = atoi(argv[1]);
	stats->time_to_die = atoi(argv[2]) * 1000;
	stats->time_to_eat = atoi(argv[3]) * 1000;
	stats->time_to_sleep = atoi(argv[4]) * 1000;
	stats->meal_eaten = 0;
	stats->meal_to_eat = 0;
}

int	main(int argc, char **argv)
{
	t_philo	**all_philos;
	t_stats	stats;
	int		nb_philos;

	if (manage_args(&stats, argc, argv))
		return (1);
	nb_philos = stats.nb_philo;
	if (nb_philos < 1)
		return (printf("Error wrong nb of philos\n"), 1);
	if (stats.meal_to_eat < 1 && stats.nb_params == 5)
		return (printf("Error passing arguments eat\n"), 1);
	all_philos = create_philos(nb_philos);
	if (!all_philos)
		return (printf("Error malloc creating philos\n"), 1);
	init_philos(all_philos, nb_philos, &stats);
	if (!init_forks(all_philos, nb_philos))
		return (printf("Error malloc initialising forks\n"), 1);
	create_thread(all_philos, nb_philos);
	free_philos(all_philos, nb_philos);
	return (0);
}
