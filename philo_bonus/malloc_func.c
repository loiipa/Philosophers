/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:34:34 by cjang             #+#    #+#             */
/*   Updated: 2021/12/20 15:20:28 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	malloc_t_philo(t_philo **p, int num)
{
	*p = (t_philo *)malloc(sizeof(t_philo) * num);
	if (!(*p))
		return (1);
	return (0);
}

static int	malloc_pid_t(pid_t **pid, int num)
{
	*pid = (pid_t *)malloc(sizeof(pid_t) * num);
	if (!(*pid))
		return (1);
	return (0);
}

int	malloc_func(t_philo **p, pid_t **pid, int num)
{
	if (malloc_t_philo(p, num) == 1)
		return (1);
	else if (malloc_pid_t(pid, num) == 1)
	{
		free(*p);
		return (1);
	}
	return (0);
}
