/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:45:40 by jelarose          #+#    #+#             */
/*   Updated: 2020/11/10 15:25:19 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

void		func_detach(t_data *data, int nb)
{
	int		i;

	sem_wait(data->print_sema);
	i = -1;
	while (++i < nb)
		data[i].state = 0;
	sem_post(data->print_sema);
}

void		*func_verif(t_data *data, int nb)
{
	int		i;

	while (1)
	{
		i = -1;
		while (++i < nb)
		{
			if ((get_ms(&data[i]) - data[i].time) > data[i].time_to_die)
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
