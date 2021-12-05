/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:26:25 by cjang             #+#    #+#             */
/*   Updated: 2021/12/05 13:34:31 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_diff(struct timeval *start, struct timeval *end)
{
	long long	sec_to_msec;
	long long	usec_to_msec;

	sec_to_msec = (end->tv_sec - start->tv_sec) * 1000;
	usec_to_msec = (end->tv_usec - start->tv_usec) / 1000;
	return (sec_to_msec + usec_to_msec);
}
