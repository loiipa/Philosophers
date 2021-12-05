/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:02:48 by cjang             #+#    #+#             */
/*   Updated: 2021/12/05 17:03:22 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_mornitor(void *p)
{
	t_philo			*philo;
	struct timeval	t_check;
	int				time_check;

	philo = (t_philo *)p;
	while (philo->cond->fin_flag == 0)
	{
		gettimeofday(&t_check, NULL);
		time_check = (int)time_diff(&philo->sleep_time, &t_check);
		if (time_check > philo->cond->time_to_die)
		{
			time_check = (int)time_diff(&philo->cond->start_time, &t_check);
			philo->cond->fin_flag = 1;
			printf("%d %d died\n", time_check, philo->index);
		}
		usleep(100);
		if (philo->cond->philo_eat_fin_count == philo->cond->num_of_philo)
			philo->cond->fin_flag = 1;
	}
	return (NULL);
}
