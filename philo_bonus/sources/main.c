/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 21:59:55 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/02/08 13:38:27 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//error output
void	write_error(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" ____________________________________________________ \n", 1);
	ft_putstr_fd("|            Please enter 4 or 5 arguments           |\n", 1);
	ft_putstr_fd("|____________________________________________________|\n", 1);
	ft_putstr_fd("|             [1][Number of philosophers]            |\n", 1);
	ft_putstr_fd("|             [2][Time to die]                       |\n", 1);
	ft_putstr_fd("|             [3][Time to eat]                       |\n", 1);
	ft_putstr_fd("|             [4][Time to sleep]                     |\n", 1);
	ft_putstr_fd("|             [5][Number of meals]                   |\n", 1);
	ft_putstr_fd("|____________________________________________________|\n", 1);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_data	data;

	init(argc, argv, &data);
	run_processes(&data);
	sem_wait(data.simulation);
	cleaning_and_completion(&data);
	return (0);
}
