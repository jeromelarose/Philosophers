/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 14:56:45 by jelarose          #+#    #+#             */
/*   Updated: 2020/11/07 17:19:28 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct			s_data
{
	pthread_t			philo;
	sem_t				*forks_sema;
	sem_t				*print_sema;
	int					num;
	int					state;
	int					number_of_philosopher;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_time_each_philosophers_must_eat;
	long long			time;
	long long			time_ori;
}						t_data;

void					ft_putstr(char *str);
void					ft_putnbr(long long nb);
int						ft_is_digit_pos(char *str);
int						ft_atoi(const char *str);
long long				get_ms(t_data *data);
void					print_msg(t_data *data, int pid, char *msg);
void					gest_philo(t_data *data);
void					*func(void *d);
int						is_all_eat(t_data *data, int nb);
void					init_data(t_data *data, int ac, char **av, int nb);
void					init_thread(t_data *data, int nb);
int						verif_av(int ac, char **av);
void					func_detach(t_data *data, int nb);
void					*func_verif(t_data *data, int nb);

#endif
