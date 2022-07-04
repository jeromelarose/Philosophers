/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 04:43:35 by jelarose          #+#    #+#             */
/*   Updated: 2020/11/10 15:20:14 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

void		init_data2(t_data *data, int nb)
{
	int		i;

	i = -1;
	data[0].time_ori = get_ms(&data[0]);
	while (++i < nb)
	{
		data[i].forks_sema = data[0].forks_sema;
		data[i].print_sema = data[0].print_sema;
		data[i].num = i;
		data[i].state = 1;
		data[i].time_ori = data[0].time_ori;
		data[i].time = 0;
		data[i].number_of_philosopher = nb;
		data[i].time_to_die = data[0].time_to_die;
		data[i].time_to_eat = data[0].time_to_eat;
		data[i].time_to_sleep = data[0].time_to_sleep;
		data[i].number_of_time_each_philosophers_must_eat =
		data[0].number_of_time_each_philosophers_must_eat;
	}
}

void		init_data(t_data *data, int ac, char **av, int nb)
{
	data[0].forks_sema = sem_open("forks", O_CREAT, S_IRWXU, nb);
	data[0].print_sema = sem_open("prints", O_CREAT, S_IRWXU, 1);
	data[0].time_ori = 0;
	data[0].time = 0;
	data[0].time_to_die = ft_atoi(av[2]);
	data[0].time_to_eat = ft_atoi(av[3]);
	data[0].time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data[0].number_of_time_each_philosophers_must_eat = ft_atoi(av[5]);
	else
		data[0].number_of_time_each_philosophers_must_eat = -1;
	init_data2(data, nb);
}

void		init_thread(t_data *data, int nb)
{
	int		i;
	int		y;

	y = -1;
	while (++y < 2)
	{
		i = y;
		while (i < nb)
		{
			pthread_create(&(data[i].philo), NULL, func,
			(void *)(&data[i]));
			i += 2;
		}
	}
}

void		gest_func(int ac, char **av)
{
	int		nb;
	int		i;
	t_data	*data;

	i = 0;
	nb = ft_atoi(av[1]);
	if (!(data = malloc(sizeof(t_data) * nb)))
		exit(-1);
	sem_unlink("prints");
	sem_unlink("forks");
	init_data(data, ac, av, nb);
	init_thread(data, nb);
	func_verif(data, nb);
	i = -1;
	while (++i < nb)
		pthread_join(data[i].philo, NULL);
	sem_unlink("prints");
	sem_unlink("forks");
	sem_close(data->print_sema);
	sem_close(data->forks_sema);
	free(data);
}

int			main(int ac, char **av)
{
	if (!verif_av(ac, av))
	{
		ft_putstr("Probleme d'arguments\n");
		return (1);
	}
	gest_func(ac, av);
	return (0);
}
