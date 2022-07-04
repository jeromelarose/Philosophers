/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:40:20 by jelarose          #+#    #+#             */
/*   Updated: 2020/11/10 15:26:47 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void		func_detach(t_data *data, int nb)
{
	int		i;

	pthread_mutex_lock(data->print_mu);
	i = -1;
	while (++i < nb)
		data[i].state = 0;
	pthread_mutex_unlock(data->print_mu);
}

void		*func_verif(t_data *data, int nb)
{
	int		i;

	while (1)
	{
		i = -1;
		while (++i < nb)
		{
			if ((get_ms(&data[i]) - data[i].time_ori) > data[i].time_to_die)
			{
				print_msg((&data[i]),
				data[i].num, " died\n");
				func_detach(data, nb);
				return ((void *)0);
			}
			if (data[i].number_of_time_each_philosophers_must_eat == 0)
				if (is_all_eat(data, nb))
					return ((void *)0);
		}
		usleep(250);
	}
	return ((void *)0);
}
