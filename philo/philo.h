/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:21:08 by cjang             #+#    #+#             */
/*   Updated: 2021/12/05 18:06:58 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define THREAD_NUM 512

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

// philo
int			ft_atoi(const char *str);

// time_func.c
long long	time_diff(struct timeval *start, struct timeval *end);

//init_func.c
int			init_t_cond(t_cond *cond, int argc, char **argv);
void		init_t_philo(t_philo *philo, int index, pthread_mutex_t *l_fork, \
												pthread_mutex_t *r_fork);
void		init_t_philo_2(t_philo *philo, t_cond *cond);

//pthread_func.c
void		*ft_mornitor(void *num);
void		*ft_thread(void *num);

#endif
