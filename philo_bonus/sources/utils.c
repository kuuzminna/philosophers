/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 11:15:23 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/02/09 16:56:53 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

long	current_time(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = 1000 * (long)tv.tv_sec + (long)tv.tv_usec / 1000;
	return (res);
}

void	ft_usleep(int ms)
{
	long	time;

	time = current_time();
	usleep(ms * 920);
	while (current_time() < time + (long)ms)
		usleep(ms * 3);
}

int	check_meals(t_data *data)
{
	if (current_time() - data->time_of_last_meal
		> data->time_to_die)
	{
		message(data, " died");
		sem_wait(data->write_sem);
		sem_post(data->simulation);
		data->dead = 1;
		sem_post(data->death_sem);
		exit(EXIT_SUCCESS);
	}
	if (data->nbr_of_meals > 0)
	{
		if (data->meals >= data->nbr_of_meals)
		{
			data->dead = 1;
			sem_post(data->simulation);
			sem_post(data->death_sem);
			return (1);
		}
	}
	return (0);
}
