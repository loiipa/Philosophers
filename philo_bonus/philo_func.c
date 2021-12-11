/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:28:29 by cjang             #+#    #+#             */
/*   Updated: 2021/12/11 18:39:50 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	eat_algorithm(t_philo *philo)
{
	unsigned int	index;
	unsigned int	num;

	index = philo->index;
	num = philo->cond->num_of_philo;
	if (num == 1)
		;
}

static void	time_print(t_philo *philo, char *message, long long ms_time)
{
	struct timeval	middle_check;
	unsigned int	time_check;

	gettimeofday(&middle_check, NULL);
	time_check = (int)time_diff(&philo->cond->start_time, &middle_check);
	if (philo->cond->fin_flag == 1)
		return ;
	sem_wait(philo->cond->print_sem);
	printf("%d %d %s\n", time_check, philo->index, message);
	sem_post(philo->cond->print_sem);
	if (ms_time > 0)
		usleep_func(philo, ms_time);
}

static void	sleep_func(t_philo *philo)
{
	struct timeval	middle_check;
	unsigned int	time_check;

	gettimeofday(&middle_check, NULL);
	time_check = (int)time_diff(&philo->cond->start_time, &middle_check);
	philo->sleep_time = middle_check;
	if (philo->cond->fin_flag == 1)
		return ;
	sem_wait(philo->cond->print_sem);
	printf("%d %d is sleeping\n", time_check, philo->index);
	sem_post(philo->cond->print_sem);
	usleep_func(philo, philo->cond->time_to_sleep);
}

static void	eat_count_func(t_philo *philo)
{
	struct timeval	middle_check;

	sem_post(philo->fork);
	sem_post(philo->fork);
	gettimeofday(&middle_check, NULL);
	philo->sleep_time = middle_check;
	sem_post(philo->cond->eat_sem);
	return ;
}

void	ft_philo_process(t_philo *philo)
{
	eat_algorithm(philo);
	if (philo->cond->num_of_philo == 1)
	{
		sem_wait(philo->fork);
		time_print(philo, "has taken a fork", 0);
		usleep_func(philo, philo->cond->time_to_die);
		sem_post(philo->fork);
		return ;
	}
	while (philo->cond->fin_flag == 0)
	{
		sem_wait(philo->fork);
		time_print(philo, "has taken a fork", 0);
		sem_wait(philo->fork);
		time_print(philo, "has taken a fork", 0);
		time_print(philo, "is eating", philo->cond->time_to_eat);
		(philo->eat_conut)++;
		if (philo->eat_conut == (unsigned int)philo->cond->limit_num_of_eat)
			return (eat_count_func(philo));
		sem_post(philo->fork);
		sem_post(philo->fork);
		sleep_func(philo);
		time_print(philo, "is thinking", 0);
	}
	return ;
}
