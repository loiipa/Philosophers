/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 15:36:08 by cjang             #+#    #+#             */
/*   Updated: 2021/12/20 14:57:06 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static unsigned int	ft_wait_time(t_cond *c, unsigned int num)
{
	unsigned int	wait_time;

	if (num % 2 == 0)
	{
		if (c->time_to_die < c->time_to_eat + 10)
			wait_time = 0;
		else
			wait_time = c->time_to_die - c->time_to_eat - 10;
	}
	else
	{
		if (c->time_to_die < c->time_to_eat * 2 + 10)
			wait_time = 0;
		else
			wait_time = c->time_to_die - c->time_to_eat * 2 - 10;
	}
	return (wait_time);
}

void	eat_algorithm(t_cond *c, t_philo *p)
{
	unsigned int	index;
	unsigned int	num;
	unsigned int	wait_time;

	index = p->index;
	num = p->cond->num_of_philo;
	if (num == 1)
		return ;
	else
		wait_time = ft_wait_time(c, num);
	if (c->time_to_sleep < wait_time)
		wait_time = c->time_to_sleep;
	usleep_func(p, wait_time);
	if (index > num / 2)
		usleep(10000);
}
