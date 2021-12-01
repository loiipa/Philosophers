/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:21:08 by cjang             #+#    #+#             */
/*   Updated: 2021/12/01 20:38:04 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_cond
{
	unsigned int		num_of_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		limit_num_of_eat;
}t_cond;

typedef struct s_philo
{
	unsigned int		index;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	// 절대적인 시간일지, 상대적인 시간일지는 아직..
	unsigned int		time_think_start;
	unsigned int		time_eat_end;
}t_philo;

// philo
int		ft_atoi(const char *str);

// time_func.c
float	time_diff(struct timeval *start, struct timeval *end);

//init_func.c
void	init_t_cond(t_cond *philo, int argc, char **argv);

//pthread_func.c
void	*ft_mornitor(void *num);
void	*ft_thread(void *num);

#endif
