/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 21:59:42 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/02/07 11:48:47 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <unistd.h>

# define ERR_ARG	"\x1b[31mInvalid number of arguments\x1b[0m\n"
# define ERR_VAL 	"\x1b[31mTinvalid argument values\x1b[0m\n"
# define ERR_MEMORY	"\x1b[31mMemory was not allocated\x1b[0m\n"

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
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals;

	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_of_write;
	pthread_t		*thrd;

	t_philo			*philos;
}					t_data;

//cleaning_and_completion.c
void	cleaning_and_completion(t_data *data, t_philo *philos);

// initialization.c 
void	init(int argc, char **argv, t_data *data);

// libft.c
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *str, int fd);
int		ft_strncmp(const char *s1, const char *s2, long n);

//main.c
void	write_error(char *str);

//message.c
void	message(t_philo *philo, char *action);
void	sleep_and_think(t_philo *philos);
void	take_forks(t_philo *philos);
void	eat(t_philo *philos);

//threads.c
void	run_threads(t_data *data);

//utils.c
long	current_time(void);
void	ft_usleep(int ms);
int		check_meals(t_philo *philos);

#endif