/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:37:31 by cjang             #+#    #+#             */
/*   Updated: 2021/12/24 23:23:17 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usleep_func(t_philo *philo, long long ms_time, struct timeval st_time)
{
	struct timeval	cur_time;
	unsigned int	time_check;

	while (philo->cond->fin_flag == 0)
	{
		gettimeofday(&cur_time, NULL);
		time_check = (unsigned int)time_diff(&st_time, &cur_time);
		if (philo->cond->num_of_philo != 1 && ms_time <= time_check)
			break ;
		usleep(USLEEP_TIME);
	}
}
