/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:26:25 by cjang             #+#    #+#             */
/*   Updated: 2021/12/11 14:58:44 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	time_diff(struct timeval *start, struct timeval *end)
{
	long long	sec_to_msec;
	long long	usec_to_msec;

	sec_to_msec = (end->tv_sec * 1000) - (start->tv_sec * 1000);
	usec_to_msec = (end->tv_usec / 1000) - (start->tv_usec / 1000);
	return (sec_to_msec + usec_to_msec);
}
