/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:22:55 by cjang             #+#    #+#             */
/*   Updated: 2021/12/01 21:06:58 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_t_cond(t_cond *cond, int argc, char **argv)
{
	cond->num_of_philo = ft_atoi(argv[1]);
	cond->time_to_die = ft_atoi(argv[2]);
	cond->time_to_eat = ft_atoi(argv[3]);
	cond->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		cond->limit_num_of_eat = ft_atoi(argv[5]);
	else
		cond->limit_num_of_eat = 0;
}

void	init_t_philo(t_philo *philo, int index, pthread_mutex_t *l_fork, \
												pthread_mutex_t *r_fork)
{
	philo->index = index;
	philo->l_fork = l_fork;
	philo->r_fork = r_fork;
	philo->time_eat_end = 0;
	philo->time_think_start = 0;
}

// 인자값이 음수일 경우 대응
