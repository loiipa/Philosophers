/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:28:29 by cjang             #+#    #+#             */
/*   Updated: 2021/12/18 16:03:11 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	time_print(t_philo *philo, char *message, long long ms_time)
{
	struct timeval	middle_check;
	unsigned int	time_check;

	if (philo->cond->fin_flag == 1)
		return ;
	pthread_mutex_lock(&philo->cond->print_mutex);
	gettimeofday(&middle_check, NULL);
	time_check = (int)time_diff(&philo->cond->start_time, &middle_check);
	printf("%d %d %s\n", time_check, philo->index, message);
	pthread_mutex_unlock(&philo->cond->print_mutex);
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

static void	*eat_count_func(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo->cond->philo_eat_fin_count++;
	return (NULL);
}

void	*ft_philo_thread(void *p)
{
	t_philo			*philo;

	philo = (t_philo *)p;
	eat_algorithm(philo[0].cond, philo);
	while (philo->cond->fin_flag == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		time_print(philo, "has taken a fork", 0);
		if (philo->cond->num_of_philo == 1)
			usleep_func(philo, philo->cond->time_to_die);
		if (philo->cond->fin_flag != 0)
			return (mutex_unlock(philo->l_fork));
		pthread_mutex_lock(philo->r_fork);
		time_print(philo, "has taken a fork", 0);
		check_time(philo);
		time_print(philo, "is eating", philo->cond->time_to_eat);
		(philo->eat_conut)++;
		if (philo->eat_conut == philo->cond->limit_num_of_eat)
			return (eat_count_func(philo));
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		time_print(philo, "is sleeping", philo->cond->time_to_sleep);
		time_print(philo, "is thinking", 0);
	}
	return (NULL);
}
