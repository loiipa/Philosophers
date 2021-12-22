/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:22:55 by cjang             #+#    #+#             */
/*   Updated: 2021/12/18 14:03:08 by cjang            ###   ########.fr       */
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
	cond->fin_flag = 0;
	cond->return_value = 0;
	cond->philo_eat_fin_count = 0;
	gettimeofday(&cond->start_time, NULL);
}

void	init_t_philo(t_cond *cond, t_philo *philo, pthread_mutex_t *fork)
{
	unsigned int	i;

	i = 0;
	while (i < cond->num_of_philo)
	{
		philo[i].index = i + 1;
		philo[i].l_fork = &fork[i];
		if (cond->num_of_philo == 1)
			philo[i].r_fork = NULL;
		else
			philo[i].r_fork = &fork[(i + 1) % cond->num_of_philo];
		philo[i].eat_conut = 0;
		philo[i].cond = cond;
		philo[i].eat_time = cond->start_time;
		i++;
	}
}
