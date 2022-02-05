/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:19:31 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/01/28 13:18:19 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void    init_data(int argc,char **argv,t_data *data)
{
    int i;
    
    i = 0;
    data->nbr_of_philo = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if  (argc == 6)
        data->nbr_of_meals = ft_atoi(argv[5]);
    else
        data->nbr_of_meals = -1;
    if(data->nbr_of_philo <=0 || data->time_to_die <= 0 || data->time_to_eat <= 0 || data->time_to_sleep <= 0 || (argc == 6 && data->nbr_of_meals <= 0))
        write_error(ERR_VAL);
    data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (data->nbr_of_philo));
	if (!data->forks)
		write_error(ERR_MEMORY);
    while (i < data->nbr_of_philo)
		pthread_mutex_init(&(data->forks[i++]), NULL);
    pthread_mutex_init(&(data->mutex_of_write), NULL);
    data->philosophers = (t_philo *)malloc(sizeof(t_philo) * (data->nbr_of_philo));
	if (!data->philosophers)
		write_error(ERR_MEMORY);
}

/*
** if philos is last his first fork is fork with id 1
*/
static void	fork_distribution(t_philo	*philosophers, t_data *data)
{
	if (philosophers->id == data->nbr_of_philo)
	{
		philosophers->fork1 = &data->forks[(philosophers->id) % data->nbr_of_philo];
		philosophers->fork2 = &data->forks[philosophers->id - 1];
	}
    else
    {
        philosophers->fork1 = &data->forks[philosophers->id - 1];
        philosophers->fork2 = &data->forks[philosophers->id];
    }
}

static void    init_philosophers(t_data *data)
{
    t_philo	*philosophers;
    int     i;
    
    i = -1;
    philosophers = (t_philo *)data->philosophers;
    while (++i < data->nbr_of_philo)
	{
		pthread_mutex_init(&philosophers[i].death_mutex, NULL);
		philosophers[i].id = i + 1;
		philosophers[i].dead = 0;
		philosophers[i].nbr_of_meals = 0;
		philosophers[i].time_of_last_meal = current_time();
		philosophers[i].limit_of_life = data->time_to_die;
		fork_distribution(&philosophers[i], data);
		philosophers[i].data = data;
        data->philosophers[i] = philosophers[i];
	}
}

void init(int argc,char **argv,t_data *data)
{
    if (argc < 5 || argc > 6)
        write_error(ERR_ARG);
    init_data(argc, argv, data);
    init_philosophers(data);
}