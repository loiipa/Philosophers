/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:35:27 by cjang             #+#    #+#             */
/*   Updated: 2021/12/28 15:01:05 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ll_check(const char *str, int sign)
{
	unsigned long long	number;

	number = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (sign == -1 && (number > 922337203685477580 || \
		(number >= 922337203685477580 && *str - '0' >= 8)))
			return (0);
		else if (sign == 1 && (number > 922337203685477580 || \
		(number >= 922337203685477580 && *str - '0' >= 7)))
			return (-1);
		number = number * 10 + *str++ - '0';
	}
	if (*str != '\0')
		return (0);
	return (number * sign);
}

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long long	number;

	sign = 1;
	number = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	return (ll_check(&(*str), sign));
}

void	usleep_func(t_philo *philo, long long ms_time, struct timeval st_time)
{
	struct timeval	cur_time;
	long long		time_check;

	usleep(ms_time * 900);
	while (philo->cond->fin_flag == 0)
	{
		gettimeofday(&cur_time, NULL);
		time_check = time_diff(&st_time, &cur_time);
		if (philo->cond->num_of_philo != 1 && ms_time <= time_check)
			break ;
		usleep(USLEEP_TIME);
	}
}

long long	time_diff(struct timeval *start, struct timeval *end)
{
	long long	sec_to_msec;
	long long	usec_to_msec;

	sec_to_msec = (end->tv_sec * 1000) - (start->tv_sec * 1000);
	usec_to_msec = (end->tv_usec / 1000) - (start->tv_usec / 1000);
	return (sec_to_msec + usec_to_msec);
}
