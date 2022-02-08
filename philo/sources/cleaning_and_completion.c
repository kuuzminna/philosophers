/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_and_completion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:45:05 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/02/08 18:50:36 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//waiting for threads, clearing allocated memory and destroying mutexes
void	cleaning_and_completion(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philo)
		pthread_join(data->thrd[i++], NULL);
	free(data->thrd);
	while (i > 0)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&philos[i].death_mutex);
		i--;
	}
	pthread_mutex_destroy(&data->mutex_of_write);
	free(philos);
	free(data);
}
