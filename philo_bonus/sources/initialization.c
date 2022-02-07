/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 11:15:15 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/02/07 11:43:20 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	init_data(int argc, char **argv, t_data *data)
{
	data->nbr_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nbr_of_meals = ft_atoi(argv[5]);
	else
		data->nbr_of_meals = -1;
	if (data->nbr_of_philo <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (argc == 6 && data->nbr_of_meals <= 0))
		write_error(ERR_VAL);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_SIMULATION);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_DEATH);
	data->forks = sem_open(SEM_FORKS, O_CREAT, 0777, data->nbr_of_philo);
	data->simulation = sem_open(SEM_SIMULATION, O_CREAT, 0777, 0);
	data->death_sem = sem_open(SEM_DEATH, O_CREAT, 0777, 1);
	data->write_sem = sem_open(SEM_WRITE, O_CREAT, 0777, 1);
	if (data->forks == SEM_FAILED || data->simulation == SEM_FAILED
		|| data->death_sem == SEM_FAILED || data-> write_sem == SEM_FAILED)
		write_error(ERR_SEM);
}

void	init(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		write_error(ERR_ARG);
	init_data(argc, argv, data);
}
