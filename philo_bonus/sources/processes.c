/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:00:52 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/02/07 15:48:05 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	*monitoring(void *datum)
{
	t_data	*data;
	int		i;

	data = (t_data *)datum;
	while (!data->dead)
	{
		usleep(500);
		i = -1;
		while (++i < data->nbr_of_philo)
		{
			sem_wait(data->death_sem);
			if (check_meals(data))
				return (NULL);
			sem_post(data->death_sem);
		}
	}
	return (NULL);
}

static void	*life_cycle(t_data *data)
{
	pthread_t	monitor;

	if (data->id % 2 == 0)
		usleep(100);
	data->time_of_last_meal = current_time();
	if (pthread_create(&monitor, NULL, &monitoring, data) != 0)
		write_error(ERROR_THREAD);
	while (!data->dead)
	{
		take_forks(data);
		eat(data);
		if (check_meals(data))
			break ;
		if (data->dead)
			break ;
		sleep_and_think(data);
	}
	pthread_join(monitor, NULL);
	return (NULL);
}

void	run_processes(t_data *data)
{
	int	i;

	i = -1;
	data->pids = (pid_t *)malloc(sizeof(pid_t) * data->nbr_of_philo);
	if (!data->pids)
		write_error(ERR_MEMORY);
	while (++i < data->nbr_of_philo)
	{
		data->pids[i] = fork();
		if (data->pids[i] < 0)
			write_error(ERR_PID);
		else if (data->pids[i] == 0)
		{
			data->id = i + 1;
			life_cycle(data);
			return ;
		}
	}
}
