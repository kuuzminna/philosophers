/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:31:27 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/02/07 12:35:11 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*life_cycle(void *data)
{
	t_philo	*philos;

	philos = (t_philo *)data;
	if (philos->id % 2 == 0)
		usleep(100);
	philos->time_of_last_meal = current_time();
	philos->start_time = current_time();
	while (!philos->dead)
	{
		take_forks(philos);
		eat(philos);
		sleep_and_think(philos);
	}
	return (NULL);
}

static int	death_check(t_philo *philos, int i)
{
	if (current_time() - philos[i].time_of_last_meal
		> philos[i].limit_of_life)
	{
		pthread_mutex_unlock(&philos[i].death_mutex);
		message(&philos[i], " died");
		i = -1;
		while (++i < philos->data->nbr_of_philo)
			philos[i].dead = 1;
		return (1);
	}
	if (philos[i].data->nbr_of_meals > 0 && check_meals(philos))
	{
		pthread_mutex_unlock(&philos[i].death_mutex);
		message(&philos[i], "Every philosopher ate at least");
		i = -1;
		while (++i < philos->data->nbr_of_philo)
			philos[i].dead = 1;
		return (1);
	}
	return (0);
}

static void	*monitoring(void *philosophers)
{
	t_philo	*philos;
	int		i;
	int		nbr_philos;

	philos = (t_philo *)philosophers;
	nbr_philos = philos[0].data->nbr_of_philo;
	while (1)
	{
		usleep(100);
		i = -1;
		while (++i < nbr_philos)
		{
			pthread_mutex_lock(&philos[i].death_mutex);
			if (death_check(philos, i))
				return (NULL);
			pthread_mutex_unlock(&philos[i].death_mutex);
		}
	}
	return (NULL);
}

void	run_threads(t_data *data)
{
	pthread_t	*threads;
	pthread_t	monitor;
	int			philos_nbr;
	int			i;

	philos_nbr = data->nbr_of_philo;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * philos_nbr);
	if (!threads)
		write_error(ERR_MEMORY);
	i = -1;
	while (++i < philos_nbr)
		pthread_create(&threads[i], NULL, life_cycle,
			(void *)&data->philos[i]);
	pthread_create(&monitor, NULL, monitoring, (void *)data->philos);
	pthread_join(monitor, NULL);
	data->thrd = threads;
}
