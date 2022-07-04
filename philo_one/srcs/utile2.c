/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 14:34:15 by jelarose          #+#    #+#             */
/*   Updated: 2020/11/01 15:38:35 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void		print_msg(t_data *data, int pid, char *msg)
{
	if (data->state)
	{
		pthread_mutex_lock(data->print_mu);
		if (data->state)
		{
			ft_putnbr(get_ms(data));
			write(1, " ", 1);
			ft_putnbr((pid + 1));
			ft_putstr(msg);
		}
		pthread_mutex_unlock(data->print_mu);
	}
}

int			is_all_eat(t_data *data, int nb)
{
	int		i;
	int		v;

	i = -1;
	v = 1;
	while (++i < nb)
	{
		if (data[i].number_of_time_each_philosophers_must_eat > 0)
			v = 0;
		else
			data[i].state = 0;
	}
	if (v)
	{
		func_detach(data, nb);
		return (1);
	}
	return (0);
}

int			verif_av(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (0);
	if (!ft_is_digit_pos(av[1]) || !ft_is_digit_pos(av[2]) ||
	!ft_is_digit_pos(av[3]) || !ft_is_digit_pos(av[4]))
		return (0);
	if (ac == 6)
	{
		if (!ft_is_digit_pos(av[5]))
			return (0);
	}
	return (1);
}

void		*gest_philo(t_data *data, int fork_left, int fork_right)
{
	while (data->state)
	{
		pthread_mutex_lock(&data->forks[fork_right]);
		pthread_mutex_lock(&data->forks[fork_left]);
		print_msg(data, data->num, " has taken a fork\n");
		print_msg(data, data->num, " has taken a fork\n");
		data->time_ori = get_ms(data);
		print_msg(data, data->num, " is eating\n");
		while (data->state && ((get_ms(data) - data->time_ori) <
		data->time_to_eat))
			usleep(2);
		print_msg(data, data->num, " is sleeping\n");
		if (data->state &&
		(data->number_of_time_each_philosophers_must_eat > 0))
			data->number_of_time_each_philosophers_must_eat--;
		pthread_mutex_unlock(&data->forks[fork_left]);
		pthread_mutex_unlock(&data->forks[fork_right]);
		while (data->state && ((get_ms(data) - data->time_ori
		- data->time_to_eat) <
		data->time_to_sleep))
			usleep(2);
		print_msg(data, data->num, " is thinking\n");
	}
	return ((void*)0);
}

void		*func(void *d)
{
	t_data		*data;
	int			fork_right;

	data = (t_data *)d;
	if (data->num == 0)
		fork_right = data->number_of_philosopher - 1;
	else
		fork_right = data->num - 1;
	gest_philo(data, data->num, fork_right);
	return ((void *)0);
}
