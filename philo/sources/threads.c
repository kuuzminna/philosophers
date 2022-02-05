/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:31:27 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/02/05 19:41:09 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void *life_cycle(void *data)
{
	t_philo *philosophers;

	philosophers = (t_philo *)data;
	if (philosophers->id % 2 == 0)
		usleep(100);
	philosophers->time_of_last_meal = current_time();
	philosophers->start_time = current_time();
	while (!philosophers->dead)
	{
		take_forks(philosophers);
		eat(philosophers);
		sleep_and_think(philosophers);
	}
	return (NULL);
}

static int death_check(t_philo *philosophers, int i)
{
	if (current_time() - philosophers[i].time_of_last_meal > philosophers[i].limit_of_life)
	{
		pthread_mutex_unlock(&philosophers[i].death_mutex);
		message(&philosophers[i], " died");
		i = -1;
		while (++i < philosophers->data->nbr_of_philo)
			philosophers[i].dead = 1;
		return (1);
	}
	if (philosophers[i].data->nbr_of_meals > 0 && check_meals(philosophers))
	{
		pthread_mutex_unlock(&philosophers[i].death_mutex);
		message(&philosophers[i], "Every philosopher ate at least");
		i = -1;
		while (++i < philosophers->data->nbr_of_philo)
			philosophers[i].dead = 1;
		return (1);
	}
	return (0);
}

static void *monitor(void *philosophers)
{
	t_philo *philos;
	int i;
	int nbr_philos;

	philos = (t_philo *)philosophers;
	nbr_philos = philos[0].data->nbr_of_philo;
	while (1)
	{
		usleep(100);
		i = -1;
		while (++i < nbr_philos)
		{
			pthread_mutex_lock(&philos[i].death_mutex);
			if (death_check(philosophers, i))
				return (NULL);
			pthread_mutex_unlock(&philos[i].death_mutex);
		}
	}
	return (NULL);
}

void run_threads(t_data *data)
{
	pthread_t *threads;
	pthread_t monik;
	int philos_nbr;
	int i;

	philos_nbr = data->nbr_of_philo;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * philos_nbr);
	if (!threads)
		write_error(ERR_MEMORY);
	i = -1;
	while (++i < philos_nbr)
		pthread_create(&threads[i], NULL, life_cycle,
					   (void *)&data->philosophers[i]);
	pthread_create(&monik, NULL, monitor, (void *)data->philosophers);
	pthread_join(monik, NULL);
	data->thrd = threads;
}
