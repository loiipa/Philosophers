/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:22:55 by cjang             #+#    #+#             */
/*   Updated: 2021/12/21 18:53:29 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_t_cond(t_cond *cond, t_sema *sema, int argc, char **argv)
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
	cond->died_sem = sema->died_sem;
	cond->eat_sem = sema->eat_sem;
	cond->print_sem = sema->print;
	cond->return_value = 0;
	gettimeofday(&cond->start_time, NULL);
}

void	init_t_philo(t_cond *cond, t_philo *philo, t_sema *sema)
{
	unsigned int	i;

	i = 0;
	while (i < cond->num_of_philo)
	{
		philo[i].index = i + 1;
		philo[i].fork = sema->fork;
		philo[i].eat_conut = 0;
		philo[i].cond = cond;
		philo[i].eat_time = cond->start_time;
		i++;
	}
}
