/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:27:13 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/02/05 19:08:03 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int	check_meals(t_philo *philosophers)
{
	int	i;
	int	nbr_philos;

	i = -1;
	nbr_philos = philosophers[0].data->nbr_of_philo;
	while (++i < nbr_philos)
	{
		if (philosophers[i].nbr_of_meals < philosophers[i].data->nbr_of_meals)
			return (0);
	}
	return (1);
}