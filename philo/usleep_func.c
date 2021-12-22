/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:37:31 by cjang             #+#    #+#             */
/*   Updated: 2021/12/18 15:44:25 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	}
}
