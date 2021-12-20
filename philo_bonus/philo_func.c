/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:28:29 by cjang             #+#    #+#             */
/*   Updated: 2021/12/20 15:26:01 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

static void	check_time(t_philo *philo)
{
	struct timeval	cur_time;
	unsigned int	time_check;

	gettimeofday(&cur_time, NULL);
	time_check = (int)time_diff(&philo->cond->start_time, &cur_time);
	philo->eat_time = cur_time;
}

static void	eat_count_func(t_philo *philo)
{
	sem_post(philo->fork);
	sem_post(philo->fork);
	sem_post(philo->cond->eat_sem);
	return ;
}

void	ft_philo_process(t_philo *philo)
{
	eat_algorithm(philo->cond, philo);
	while (philo->cond->fin_flag == 0)
	{
		sem_wait(philo->fork);
		time_print(philo, "has taken a fork", 0);
		if (philo->cond->num_of_philo == 1)
			usleep_func(philo, philo->cond->time_to_die);
		if (philo->cond->fin_flag != 0)
			return (sem_post_func(philo->fork));
		sem_wait(philo->fork);
		time_print(philo, "has taken a fork", 0);
		check_time(philo);
		time_print(philo, "is eating", philo->cond->time_to_eat);
		(philo->eat_conut)++;
		if (philo->eat_conut == philo->cond->limit_num_of_eat)
			return (eat_count_func(philo));
		sem_post(philo->fork);
		sem_post(philo->fork);
		time_print(philo, "is sleeping", philo->cond->time_to_sleep);
		time_print(philo, "is thinking", 0);
	}
}
