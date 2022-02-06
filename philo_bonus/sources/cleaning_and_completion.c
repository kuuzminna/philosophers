/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_and_completion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 11:15:12 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/02/06 14:09:02 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	cleaning_and_completion(t_data *data)
{
	int	i;
	int	var;

	waitpid(-1, &var, 0);
	i = 0;
	if (var == 0)
	{
		while (i < data->nbr_of_philo)
			kill(data->pids[i++], SIGTERM);
	}
	free(data->pids);
	sem_unlink(SEM_SIMULATION);
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_FORKS);
	sem_close(data->simulation);
	sem_close(data->death_sem);
	sem_close(data->forks);
	sem_close(data->write_sem);
}
