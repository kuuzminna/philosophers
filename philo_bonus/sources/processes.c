/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:00:52 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/02/07 11:24:41 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	*life_cycle(t_data *data)
{
	pthread_t	monitor;

	if (data->id % 2 == 0)
		usleep(100);
	data->time_of_last_meal = current_time();
	data->start_time = current_time();
	if (pthread_create(&monitor, NULL, &monitoring, data) != 0)
		exit(1);
	while (!data->dead)
	{
		take_forks(data);
		eat(data);
		if (data->dead)
			break ;
		sleep_and_think(data);
	}
	pthread_join(monitor, NULL);
	return (NULL);
}

static void	*monitoring(void *datum)
{
	t_data	*data;
	int		i;
	int		nbr_philos;

	data = (t_data *)datum;
	nbr_philos = data->nbr_of_philo;
	while (1)
	{
		usleep(100);
		i = -1;
		while (++i < nbr_philos)
		{
			sem_wait(data->death_sem);
			if (check_meals(data))
				return (NULL);
			sem_post(data->death_sem);
		}
	}
	return (NULL);
}

void	run_processes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_of_philo)
	{
		data->pids[i] = fork();
		if (data->pids[i] < 0)
			write_error(ERR_PID);
		else if (data->pids[i] == 0)
		{
			data->id = i + 1;
			life_cycle(data);
			exit(0);
		}
		usleep(100);
	}
}
