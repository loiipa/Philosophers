/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:22:55 by cjang             #+#    #+#             */
/*   Updated: 2021/12/05 17:31:49 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_t_cond(t_cond *cond, int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
		if (ft_atoi(argv[i++]) <= 0)
			return (1);
	cond->num_of_philo = ft_atoi(argv[1]);
	cond->time_to_die = ft_atoi(argv[2]);
	cond->time_to_eat = ft_atoi(argv[3]);
	cond->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		cond->limit_num_of_eat = ft_atoi(argv[5]);
	else
		cond->limit_num_of_eat = -1;
	cond->fin_flag = 0;
	cond->philo_eat_fin_count = 0;
	gettimeofday(&cond->start_time, NULL);
	return (0);
}

void	init_t_philo(t_philo *philo, int index, pthread_mutex_t *l_fork, \
												pthread_mutex_t *r_fork)
{
	philo->index = index;
	philo->l_fork = l_fork;
	philo->r_fork = r_fork;
	philo->eat_conut = 0;
}

void	init_t_philo_2(t_philo *philo, t_cond *cond)
{
	philo->cond = cond;
	philo->sleep_time = cond->start_time;
}
