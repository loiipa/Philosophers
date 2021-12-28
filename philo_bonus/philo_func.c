/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:28:29 by cjang             #+#    #+#             */
/*   Updated: 2021/12/28 15:08:15 by cjang            ###   ########.fr       */
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

static void	eat_algorithm(t_cond *c, t_philo *p)
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
	usleep_func(p, wait_time, p->eat_time);
	if (index > num / 2)
		usleep(10000);
}

static void	time_print(t_philo *philo, char *mes, long long ms_time, int flag)
{
	struct timeval	cur_time;
	long long		time_check;

	if (philo->cond->fin_flag == 1)
		return ;
	sem_wait(philo->cond->print_sem);
	gettimeofday(&cur_time, NULL);
	time_check = (int)time_diff(&philo->cond->start_time, &cur_time);
	if (flag == 1)
		philo->eat_time = cur_time;
	if (philo->cond->fin_flag == 1)
	{
		sem_post(philo->cond->print_sem);
		return ;
	}
	printf("%lld %d %s\n", time_check, philo->index, mes);
	sem_post(philo->cond->print_sem);
	if (ms_time > 0)
		usleep_func(philo, ms_time, cur_time);
}

static void	eat_count_func(t_philo *philo)
{
	sem_post(philo->fork);
	sem_post(philo->fork);
	sem_post(philo->cond->eat_sem);
	philo->cond->fin_flag = 1;
	return ;
}

void	ft_philo_process(t_philo *philo)
{
	eat_algorithm(philo->cond, philo);
	while (philo->cond->fin_flag == 0)
	{
		sem_wait(philo->fork);
		time_print(philo, "has taken a fork", 0, 0);
		if (philo->cond->num_of_philo == 1)
			usleep_func(philo, philo->cond->time_to_die, philo->eat_time);
		if (philo->cond->fin_flag != 0)
			return (sem_post_func(philo->fork));
		sem_wait(philo->fork);
		time_print(philo, "has taken a fork", 0, 0);
		time_print(philo, "is eating", philo->cond->time_to_eat, 1);
		(philo->eat_conut)++;
		if (philo->eat_conut == philo->cond->limit_num_of_eat)
			return (eat_count_func(philo));
		sem_post(philo->fork);
		sem_post(philo->fork);
		time_print(philo, "is sleeping", philo->cond->time_to_sleep, 0);
		time_print(philo, "is thinking", 0, 0);
	}
}
