/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 21:59:52 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/02/06 15:07:25 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
#include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>

# define ERR_ARG	"\x1b[31mInvalid number of arguments\x1b[0m\n"
# define ERR_VAL 	"\x1b[31mTinvalid argument values\x1b[0m\n"
# define ERR_MEMORY	"\x1b[31mMemory was not allocated\x1b[0m\n"
# define ERR_SEM	"\x1b[31mSemaphore's error\x1b[0m\n"
# define ERR_PID	"\x1b[31mProcess error\x1b[0m\n"

# define SEM_FORKS		"/forks"
# define SEM_SIMULATION	"/simulation"
# define SEM_DEATH		"/death"
# define SEM_WRITE		"/write"

typedef struct s_data
{
	int				id;
	pid_t			*pids;

	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals;
	int				meals;
	time_t			time_of_last_meal;
	time_t			start_time;
	int				dead;

	sem_t			*forks;
	sem_t			*simulation;
	sem_t			*write_sem;
	sem_t			*death_sem;

}					t_data;
//cleaning_and_completion.c
void	cleaning_and_completion(t_data *data);

// initialization.c 
void	init(int argc,char **argv,t_data *data);

// libft.c
int     ft_atoi(const char *str);
void    ft_putstr_fd(char *str, int fd);
int		ft_strncmp(const char *s1, const char *s2, long n);

//main.c
void	write_error(char *str);

//message.c
void	message(t_data *data, char *action);
void	sleep_and_think(t_data *data);
void	take_forks(t_data *data);
void	eat(t_data *data);

//processes.c 
void run_processes(t_data *data);

//utils.c
long	current_time(void);
void	ft_usleep(int ms);
int		check_meals(t_data *data);

#endif