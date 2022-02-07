/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:19:31 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/02/07 12:05:01 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_data(int argc, char **argv, t_data *data)
{
	int	i;

	i = 0;
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
	data->forks = (pthread_mutex_t *)malloc
		(sizeof(pthread_mutex_t) *(data->nbr_of_philo));
	if (!data->forks)
		write_error(ERR_MEMORY);
	while (i < data->nbr_of_philo)
		pthread_mutex_init(&(data->forks[i++]), NULL);
	pthread_mutex_init(&(data->mutex_of_write), NULL);
	data->philos = (t_philo *)malloc(sizeof(t_philo) *(data->nbr_of_philo));
	if (!data->philos)
		write_error(ERR_MEMORY);
}

/*
** if philos is last his first fork is fork with id 1
*/
static void	fork_distribution(t_philo	*philos, t_data *data)
{
	if (philos->id == data->nbr_of_philo)
	{
		philos->fork1 = &data->forks[(philos->id)
			% data->nbr_of_philo];
		philos->fork2 = &data->forks[philos->id - 1];
	}
	else
	{
		philos->fork1 = &data->forks[philos->id - 1];
		philos->fork2 = &data->forks[philos->id];
	}
}

static void	init_philosophers(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = -1;
	philos = (t_philo *)data->philos;
	while (++i < data->nbr_of_philo)
	{
		pthread_mutex_init(&philos[i].death_mutex, NULL);
		philos[i].id = i + 1;
		philos[i].dead = 0;
		philos[i].nbr_of_meals = 0;
		philos[i].time_of_last_meal = current_time();
		philos[i].limit_of_life = data->time_to_die;
		fork_distribution(&philos[i], data);
		philos[i].data = data;
		data->philos[i] = philos[i];
	}
}

void	init(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		write_error(ERR_ARG);
	init_data(argc, argv, data);
	init_philosophers(data);
}
