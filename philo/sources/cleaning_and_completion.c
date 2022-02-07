/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_and_completion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:45:05 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/02/07 11:48:47 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
