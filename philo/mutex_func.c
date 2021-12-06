/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:10:43 by cjang             #+#    #+#             */
/*   Updated: 2021/12/06 16:51:32 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_init(t_cond *cond, pthread_mutex_t *fork)
{
	unsigned int	i;

	i = 0;
	while (i < cond->num_of_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
}

void	mutex_destroy(t_cond *cond, pthread_mutex_t *fork)
{
	unsigned int	i;

	i = 0;
	while (i <= cond->num_of_philo)
	{
		pthread_mutex_destroy(&fork[i]);
		i++;
	}
}
