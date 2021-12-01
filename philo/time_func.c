/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:26:25 by cjang             #+#    #+#             */
/*   Updated: 2021/12/01 20:26:35 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

float	time_diff(struct timeval *start, struct timeval *end)
{
	float	sec_to_msec;
	float	usec_to_msec;

	sec_to_msec = 1e+3 * (end->tv_sec - start->tv_sec);
	usec_to_msec = 1e-3 * (end->tv_usec - start->tv_usec);
	return (sec_to_msec + usec_to_msec);
}
