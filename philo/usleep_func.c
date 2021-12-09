/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:37:31 by cjang             #+#    #+#             */
/*   Updated: 2021/12/09 16:24:47 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	died_check(t_philo *philo, struct timeval *middle_check)
{
	unsigned int	time_check;

	time_check = (int)time_diff(&philo->sleep_time, middle_check);
	if (time_check >= philo->cond->time_to_die)
	{
		time_check = (int)time_diff(&philo->cond->start_time, middle_check);
		if (philo->cond->fin_flag == 0)
		{
			philo->cond->fin_flag = 1;
			pthread_mutex_lock(&philo->cond->print_mutex);
			printf("%d %d died\n", time_check, philo->index);
			pthread_mutex_unlock(&philo->cond->print_mutex);
		}
	}
}

void	usleep_func(t_philo *philo, long long ms_time)
{
	struct timeval	start_check;
	struct timeval	middle_check;
	unsigned int	time_check;

	gettimeofday(&start_check, NULL);
	while (philo->cond->fin_flag == 0)
	{
		gettimeofday(&middle_check, NULL);
		time_check = (unsigned int)time_diff(&start_check, &middle_check);
		if (philo->cond->num_of_philo != 1 && ms_time <= time_check)
			break ;
		usleep(USLEEP_TIME);
		died_check(philo, &middle_check);
	}
}
