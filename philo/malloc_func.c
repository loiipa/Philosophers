/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:34:34 by cjang             #+#    #+#             */
/*   Updated: 2021/12/08 16:39:05 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	malloc_t_philo(t_philo **p, int num)
{
	*p = (t_philo *)malloc(sizeof(t_philo) * num);
	if (!(*p))
		return (1);
	return (0);
}

static int	malloc_pthread_t(pthread_t **p_t, int num)
{
	*p_t = (pthread_t *)malloc(sizeof(t_philo) * num);
	if (!(*p_t))
		return (1);
	return (0);
}

static int	malloc_pthread_mutex_t(pthread_mutex_t **f, int num)
{
	*f = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num);
	if (!(*f))
		return (1);
	return (0);
}

int	malloc_func(t_philo **p, pthread_t **p_t, pthread_mutex_t **f, int num)
{
	if (malloc_t_philo(p, num) == 1)
		return (1);
	if (malloc_pthread_t(p_t, num) == 1)
	{
		free(*p);
		return (1);
	}
	if (malloc_pthread_mutex_t(f, num) == 1)
	{
		free(*p);
		free(*p_t);
		return (1);
	}
	return (0);
}
