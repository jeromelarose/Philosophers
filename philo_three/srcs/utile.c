/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 14:57:56 by jelarose          #+#    #+#             */
/*   Updated: 2020/10/27 17:52:19 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void		ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}

void		ft_putnbr(long long nb)
{
	char	c;

	c = '-';
	if (nb < 0)
	{
		write(1, &c, 1);
		nb *= -1;
	}
	if ((nb / 10) > 0)
		ft_putnbr(nb / 10);
	c = (nb % 10 + '0');
	write(1, &c, 1);
}

int			ft_is_digit_pos(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] == '+')
		i++;
	if (str[i] == '0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int			ft_atoi(const char *str)
{
	int		neg;
	int		res;

	res = 0;
	neg = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v' ||
			*str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * neg);
}

long long	get_ms(t_data *data)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000LL - data->time;
	return (milliseconds);
}
