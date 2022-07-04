/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 04:43:35 by jelarose          #+#    #+#             */
/*   Updated: 2020/11/12 17:27:12 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void		*func_veri(t_data *data)
{
	while (data->state)
	{
		if (((get_ms(data)) - data->time_ori) >
		data->time_to_die)
		{
			print_msg(data, data->num, " died\n");
			sem_wait(data->print);
			sem_post(data->dead);
			pthread_join(data->v_dead, NULL);
			data->state = 0;
			data->died = 1;
			sem_post(data->print);
			break ;
		}
		if (data->number_of_time_each_philosophers_must_eat == 0)
		{
			data->state = 0;
			break ;
		}
		usleep(250);
	}
	return ((void *)0);
}

void		init_data(t_data *data, int ac, char **av, int nb)
{
	data->number_of_philosopher = nb;
	data->time = 0;
	data->time_ori = 0;
	data->state = 1;
	data->died = 0;
	data->pass = sem_open("pass", O_CREAT, S_IRWXU, 0);
	data->end = sem_open("end", O_CREAT, S_IRWXU, 0);
	data->fork = sem_open("forks", O_CREAT, S_IRWXU, nb);
	data->print = sem_open("prints", O_CREAT, S_IRWXU, 1);
	data->dead = sem_open("dead", O_CREAT, S_IRWXU, 0);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->number_of_time_each_philosophers_must_eat =
		ft_atoi(av[5]);
	else
		data->number_of_time_each_philosophers_must_eat = -1;
	data->time = get_ms(data);
}

void		gest_fils(t_data *data)
{
	pthread_create(&(data->v_dead), NULL, isdead,
	(void *)(data));
	pthread_create(&(data->philo), NULL, func,
	(void *)(data));
	func_veri(data);
	pthread_join(data->philo, NULL);
	sem_close(data->print);
	sem_close(data->fork);
	if (data->died)
	{
		pthread_join(data->v_dead, NULL);
		sem_close(data->dead);
		sem_post(data->pass);
		sem_close(data->pass);
		sem_post(data->end);
		sem_close(data->end);
		exit(0);
	}
	sem_post(data->pass);
	sem_close(data->pass);
	pthread_join(data->v_dead, NULL);
	sem_close(data->dead);
	sem_post(data->end);
	sem_close(data->end);
}

void		gest(t_data *data, int nb)
{
	int			i;
	int			pid;

	i = -1;
	while (++i < nb)
	{
		pid = fork();
		if (pid == 0)
			break ;
	}
	if (pid == 0)
	{
		data->num = i;
		gest_fils(data);
		exit(0);
	}
}

int			main(int ac, char **av)
{
	t_data		data;
	int			i;
	int			nb;

	if (!verif_av(ac, av))
	{
		ft_putstr("Probleme d'arguments\n");
		return (1);
	}
	nb = ft_atoi(av[1]);
	ft_unlink();
	init_data(&data, ac, av, nb);
	gest(&data, nb);
	i = -1;
	while (++i < nb)
		sem_wait(data.pass);
	sem_post(data.dead);
	i = -1;
	while (++i < nb)
		sem_wait(data.end);
	usleep(100000);
	ft_unlink();
	ft_close(&data);
	return (0);
}
