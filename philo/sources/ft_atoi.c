/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:16:57 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/01/27 11:33:22 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h "

static int	ft_isspace(char c)
{
	if (c == '\n' || c == '\t' || c == '\v' || c == ' '
		|| c == '\r' || c == '\f')
		return(1);
	else
		return(0);
}
int     ft_atoi(const char *str)
{
    int			i;
	int			neg;
	long long	nb;

	i = 0;
	nb = 0;
	neg = 1;
	while(ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -neg;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	if (nb > INT_MAX && sign == 1)
		return (-1);
	if (nb > (long long)INT_MAX + 1 && sign == -1)
		return (0);
	return (nb * neg);
}

void    ft_putstr_fd(char *str, int fd)
{
    int i;
    
    i = 0;
    if (!str)
        while(str[i])
            write(fd, &str[i++], 1);
}