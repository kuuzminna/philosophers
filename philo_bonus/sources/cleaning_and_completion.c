/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_and_completion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 11:15:12 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/02/07 15:03:50 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	cleaning_and_completion(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philo)
		kill(data->pids[i++], SIGKILL);
	free(data->pids);
	sem_close(data->simulation);
	sem_close(data->death_sem);
	sem_close(data->forks);
	sem_close(data->write_sem);
}
