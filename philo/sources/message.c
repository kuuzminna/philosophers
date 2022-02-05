/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:11:59 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/02/05 19:14:44 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	message(t_philo *philo, char *action)
{
	int	timestamp;

	timestamp = current_time() - philo->start_time;
	pthread_mutex_lock(&philo->data->mutex_of_write);
	if (ft_strncmp(action, "Every philosopher ate at least", 30))
		printf("%d %d %s\n", timestamp, philo->id, action);
	else
		printf("%d %s %d %s\n", timestamp, action, philo->data->nbr_of_meals, "times");
	pthread_mutex_unlock(&philo->data->mutex_of_write);
}

void	sleep_and_think(t_philo *philosophers)
{
	message(philosophers, "is sleeping");
	ft_usleep(philosophers->data->time_to_sleep);
	message(philosophers, "is thinking");
}

void	take_forks(t_philo *philosophers)
{
    pthread_mutex_lock(philosophers->fork1);
	message(philosophers, "has taken a fork");
    pthread_mutex_lock(philosophers->fork2);
    message(philosophers, "has taken a fork");
}

void	eat(t_philo *philosophers)
{
	message(philosophers, "is eating");
    philosophers->time_of_last_meal = current_time();
	philosophers->nbr_of_meals++;
    ft_usleep(philosophers->data->time_to_eat);
	pthread_mutex_unlock(philosophers->fork2);
	pthread_mutex_unlock(philosophers->fork1);
}