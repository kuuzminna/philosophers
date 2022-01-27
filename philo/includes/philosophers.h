/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 21:59:42 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/01/27 11:37:41 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				dead;
	int				nbr_of_meals;
	time_t			time_of_last_meal;
	time_t			limit_of_life;
	time_t			start_time;

	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	pthread_mutex_t	death_mutex;

	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals;

	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_t		*tids;

	t_philo			*philosophers;
}					t_data;

// initialization.c 

// libft.c
int     ft_atoi(const char *str);
void    ft_putstr_fd(char *str, int fd);

#endif