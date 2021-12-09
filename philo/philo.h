/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:21:08 by cjang             #+#    #+#             */
/*   Updated: 2021/12/09 16:30:41 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define USLEEP_TIME 100

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_cond
{
	unsigned int		num_of_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	int					limit_num_of_eat;
	int					fin_flag;
	unsigned int		philo_eat_fin_count;
	struct timeval		start_time;
	pthread_mutex_t		print_mutex;
}t_cond;

typedef struct s_philo
{
	unsigned int		index;
	unsigned int		eat_conut;
	int					fin_flag;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	t_cond				*cond;
	struct timeval		sleep_time;
}t_philo;

// utils
int			ft_atoi(const char *str);

// time_func.c
long long	time_diff(struct timeval *start, struct timeval *end);

//init_func.c
void		init_t_cond(t_cond *cond, int argc, char **argv);
void		init_t_philo(t_cond *cond, t_philo *philo, pthread_mutex_t *fork);

//philo_func.c
void		*ft_philo_thread(void *num);

// print_func.c
int			print_return(char *s, int i);

// malloc_func.c
int			malloc_func(t_philo **p, pthread_t **p_t, pthread_mutex_t **f, \
						int num);

// free_func.c
void		free_func(t_philo **p, pthread_t **p_t, pthread_mutex_t **f);

// mutex_func.c
void		mutex_init(t_cond *cond, pthread_mutex_t *fork);
void		mutex_destroy(t_cond *cond, pthread_mutex_t *fork);
void		*mutex_unlock(pthread_mutex_t *fork);

// pthread_func.c
void		pthread_create_func(t_cond *c, t_philo *p, pthread_t *p_t);
void		pthread_join_func(t_cond *cond, pthread_t *philo_thread);

// usleep_func.c
void		usleep_func(t_philo *philo, long long ms_time);

#endif
