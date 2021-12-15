/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:35:27 by cjang             #+#    #+#             */
/*   Updated: 2021/12/11 14:58:42 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	return (number * sign);
}
