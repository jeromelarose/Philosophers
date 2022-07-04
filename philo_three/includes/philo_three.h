/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 21:39:33 by jelarose          #+#    #+#             */
/*   Updated: 2020/11/11 15:54:05 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct			s_data
{
	pthread_t			philo;
	pthread_t			inspect;
	pthread_t			v_dead;
	sem_t				*fork;
	sem_t				*print;
	sem_t				*dead;
	sem_t				*pass;
	sem_t				*end;
	long long			time;
	long long			time_ori;
	int					state;
	int					died;
	int					pid;
	int					num;
	int					number_of_philosopher;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_time_each_philosophers_must_eat;
}						t_data;

void					ft_close(t_data *data);
void					ft_unlink();
void					ft_putstr(char *str);
void					ft_putnbr(long long nb);
int						ft_is_digit_pos(char *str);
int						ft_atoi(const char *str);
long long				get_ms(t_data *data);
void					print_msg(t_data *data, int pid, char *msg);
void					gest_philo(t_data *data);
void					*func(void *d);
void					init_data(t_data *data, int ac,
						char **av, int nb);
int						verif_av(int ac, char **av);
void					*isdead(void *d);

#endif
