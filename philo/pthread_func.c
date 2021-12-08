/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:08:08 by cjang             #+#    #+#             */
/*   Updated: 2021/12/08 17:36:42 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pthread_create_func(t_cond *c, t_philo *p, pthread_t *p_t)
{
	unsigned int	i;
	int				check;

	i = 0;
	while (i < c->num_of_philo)
	{
		check = pthread_create(&p_t[i], NULL, ft_philo_thread, \
								(void *)&p[i]);
		if (check != 0)
		{
			printf("pthread_create error\n");
			return ;
		}
		i++;
	}
}

void	pthread_join_func(t_cond *cond, pthread_t *philo_thread)
{
	unsigned int	i;
	int				check;

	i = 0;
	while (i < cond->num_of_philo)
	{
		check = pthread_join(philo_thread[i], NULL);
		if (check != 0)
		{
			printf("pthread_join error\n");
			return ;
		}
		i++;
	}
}
