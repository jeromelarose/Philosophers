/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:25:57 by jelarose          #+#    #+#             */
/*   Updated: 2020/11/12 17:27:33 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void		ft_unlink(void)
{
	sem_unlink("pass");
	sem_unlink("prints");
	sem_unlink("forks");
	sem_unlink("dead");
	sem_unlink("end");
}

void		ft_close(t_data *data)
{
	sem_close(data->pass);
	sem_close(data->print);
	sem_close(data->fork);
	sem_close(data->dead);
	sem_close(data->end);
}
