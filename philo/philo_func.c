/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:28:29 by cjang             #+#    #+#             */
/*   Updated: 2021/12/07 15:21:49 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat_algorithm(t_philo *philo)
{
	unsigned int	index;
	unsigned int	num;

	index = philo->index;
	num = philo->cond->num_of_philo;
	if (index % 2 == 0)
		usleep(1000);
	else if (num % 2 == 1 && index == num)
		usleep(1000);
}

static void	time_print(t_philo *philo, char *message, long long ms_time)
{
	struct timeval	start_check;
	struct timeval	middle_check;
	unsigned int	time_check;

	gettimeofday(&middle_check, NULL);
	time_check = (int)time_diff(&philo->cond->start_time, &middle_check);
	if (philo->cond->fin_flag == 1)
		return ;
	pthread_mutex_lock(&philo->cond->print_mutex);
	printf("%d %d %s\n", time_check, philo->index, message);
	pthread_mutex_unlock(&philo->cond->print_mutex);
	gettimeofday(&start_check, NULL);
	if (ms_time > 0)
	{
		while (1)
		{
			gettimeofday(&middle_check, NULL);
			time_check = (unsigned int)time_diff(&start_check, &middle_check);
			if (ms_time <= time_check)
				break ;
			usleep(USLEEP_TIME);
		}
	}
}

static void	sleep_func(t_philo *philo)
{
	struct timeval	start_check;
	struct timeval	middle_check;
	unsigned int	time_check;

	gettimeofday(&middle_check, NULL);
	time_check = (int)time_diff(&philo->cond->start_time, &middle_check);
	philo->sleep_time = middle_check;
	if (philo->cond->fin_flag == 1)
		return ;
	pthread_mutex_lock(&philo->cond->print_mutex);
	printf("%d %d is sleeping\n", time_check, philo->index);
	pthread_mutex_unlock(&philo->cond->print_mutex);
	gettimeofday(&start_check, NULL);
	while (1)
	{
		gettimeofday(&middle_check, NULL);
		time_check = (int)time_diff(&start_check, &middle_check);
		if (philo->cond->time_to_sleep <= time_check)
			break ;
		usleep(USLEEP_TIME);
	}
}

static void	*eat_count_func(t_philo *philo)
{
	struct timeval	middle_check;

	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	gettimeofday(&middle_check, NULL);
	philo->sleep_time = middle_check;
	philo->cond->philo_eat_fin_count++;
	return (NULL);
}

void	*ft_philo_thread(void *p)
{
	t_philo			*philo;

	philo = (t_philo *)p;
	eat_algorithm(philo);
	while (philo->cond->fin_flag == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		time_print(philo, "has taken a fork", 0);
		if (philo->cond->fin_flag != 0)
		{
			pthread_mutex_unlock(philo->l_fork);
			break ;
		}
		pthread_mutex_lock(philo->r_fork);
		time_print(philo, "has taken a fork", 0);
		time_print(philo, "is eating", philo->cond->time_to_eat);
		(philo->eat_conut)++;
		if (philo->eat_conut == (unsigned int)philo->cond->limit_num_of_eat)
			eat_count_func(philo);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		sleep_func(philo);
		time_print(philo, "is thinking", 0);
	}
	return (NULL);
}
