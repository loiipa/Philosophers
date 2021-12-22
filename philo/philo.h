/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:21:08 by cjang             #+#    #+#             */
/*   Updated: 2021/12/18 15:59:29 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define USLEEP_TIME 200

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_cond
{
	unsigned int		num_of_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		limit_num_of_eat;
	int					fin_flag;
	int					return_value;
	unsigned int		pthread_success;
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
	struct timeval		eat_time;
}t_philo;

int			ft_atoi(const char *str);

long long	time_diff(struct timeval *start, struct timeval *end);

void		init_t_cond(t_cond *cond, int argc, char **argv);
void		init_t_philo(t_cond *cond, t_philo *philo, pthread_mutex_t *fork);

void		*ft_philo_thread(void *num);

int			print_return(char *s, int i);

int			malloc_func(t_philo **p, pthread_t **p_t, pthread_mutex_t **f, \
			int num);
void		free_func(t_philo **p, pthread_t **p_t, pthread_mutex_t **f);

int			mutex_init(t_cond *cond, pthread_mutex_t *fork);
void		mutex_destroy(t_cond *cond, pthread_mutex_t *fork);
void		*mutex_unlock(pthread_mutex_t *fork);

void		pthread_create_func(t_cond *c, t_philo *p, pthread_t *p_t);
void		pthread_join_func(unsigned int num, t_cond *c, pthread_t *p_t);

void		usleep_func(t_philo *philo, long long ms_time);

void		eat_algorithm(t_cond *c, t_philo *p);
#endif
