/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 11:15:20 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/02/07 11:30:05 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	message(t_data *data, char *action)
{
	int	timestamp;

	timestamp = current_time() - data->start_time;
	sem_wait(data->write_sem);
	printf("%d %d %s\n", timestamp, data->id, action);
	sem_post(data->write_sem);
}

void	take_forks(t_data *data)
{
	sem_wait(data->forks);
	message(data, "has taken a fork");
	sem_wait(data->forks);
	message(data, "has taken a fork");
	sem_wait(data->death_sem);
}

void	eat(t_data *data)
{
	message(data, "is eating");
	data->time_of_last_meal = current_time();
	sem_post(data->death_sem);
	ft_usleep(data->time_to_eat);
	data->meals++;
	sem_post(data->forks);
	sem_post(data->forks);
}

void	sleep_and_think(t_data *data)
{
	message(data, "is sleeping");
	ft_usleep(data->time_to_sleep);
	message(data, "is thinking");
}
