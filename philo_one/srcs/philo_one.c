/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 14:12:10 by jelarose          #+#    #+#             */
/*   Updated: 2020/11/10 15:08:01 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void		init_data2(t_data *data, int nb)
{
	int		i;

	i = -1;
	data[0].time = get_ms(&data[0]);
	while (++i < nb)
	{
		data[i].forks = data[0].forks;
		data[i].print_mu = data[0].print_mu;
		data[i].num = i;
		data[i].state = 1;
		data[i].time_ori = 0;
		data[i].time = data[0].time;
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
	int		i;

	if (!(data[0].forks = malloc(sizeof(pthread_mutex_t) * nb)))
		exit(-1);
	if (!(data[0].print_mu = malloc(sizeof(pthread_mutex_t) * 1)))
		exit(-1);
	i = -1;
	while (++i < nb)
		pthread_mutex_init(&data[0].forks[i], NULL);
	pthread_mutex_init(data[0].print_mu, NULL);
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
	init_data(data, ac, av, nb);
	init_thread(data, nb);
	func_verif(data, nb);
	i = -1;
	while (++i < nb)
		pthread_join(data[i].philo, NULL);
	pthread_mutex_destroy(data[0].print_mu);
	pthread_mutex_destroy(data[0].forks);
	free(data[0].forks);
	free(data[0].print_mu);
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
