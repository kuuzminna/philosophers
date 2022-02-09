/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrapefr <ggrapefr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:16:57 by ggrapefr          #+#    #+#             */
/*   Updated: 2022/02/09 16:34:07 by ggrapefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// converting a string into a numeric form, processing one sign of a number and the number itself, no more!!
int	ft_atoi(const char *str)
{
	int			i;
	int			neg;
	long long	nb;

	i = 0;
	nb = 0;
	neg = 1;
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
	if (str[i] || (nb > INT_MAX && neg == 1))
		return (-1);
	if (nb > (long long)INT_MAX + 1 && neg == -1)
		return (-1);
	return (nb * neg);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			write(fd, &str[i++], 1);
}

int	ft_strncmp(const char *s1, const char *s2, long n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	if (n == 0)
		return (0);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (*str1 && *str2 && --n && *(str1) == *(str2))
	{
		str1++;
		str2++;
	}
	return (*(str1) - *(str2));
}
