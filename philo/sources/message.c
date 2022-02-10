/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:11:59 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/02/10 20:27:09 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// message output
void	message(t_philo *philo, char *action)
{
	int	timestamp;

	timestamp = current_time() - philo->start_time;
	pthread_mutex_lock(&philo->data->mutex_of_write);
	if (ft_strncmp(action, "Every philosopher ate at least", 30))
		printf("%d %d %s\n", timestamp, philo->id, action);
	else
		printf("%d %s %d %s\n", timestamp, action,
			philo->data->nbr_of_meals, "times");
	pthread_mutex_unlock(&philo->data->mutex_of_write);
}

void	sleep_and_think(t_philo *philos)
{
	message(philos, "is sleeping");
	ft_usleep(philos->data->time_to_sleep);
	message(philos, "is thinking");
}

void	take_forks(t_philo *philos)
{
	pthread_mutex_lock(philos->fork1);
	message(philos, "has taken a fork");
	pthread_mutex_lock(philos->fork2);
	message(philos, "has taken a fork");
}

void	eat(t_philo *philos)
{
	message(philos, "is eating");
	philos->time_of_last_meal = current_time();
	philos->nbr_of_meals++;
	ft_usleep(philos->data->time_to_eat);
	pthread_mutex_unlock(philos->fork2);
	pthread_mutex_unlock(philos->fork1);
}
