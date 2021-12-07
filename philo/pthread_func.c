/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:08:08 by cjang             #+#    #+#             */
/*   Updated: 2021/12/06 16:51:15 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pthread_create_func(t_cond *c, t_philo *p, pthread_t *p_t)
{
	unsigned int	i;
	int				check;
	void			(*fp)();

	i = 0;
	while (i < c->num_of_philo * 2)
	{
		if (i % 2 == 0)
			fp = (void *)ft_philo_thread;
		else
			fp = (void *)ft_mornitor;
		check = pthread_create(&p_t[i], NULL, (void *)fp, (void *)&p[i / 2]);
		if (check != 0)
		{
			printf("pthread_create error\n");
			return ;
		}
		i++;
	}
}

static void	pthread_join_func(t_cond *cond, pthread_t *philo_thread)
{
	unsigned int	i;
	int				check;

	i = 0;
	while (i < cond->num_of_philo * 2)
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

void	pthread_func(t_cond *cond, t_philo *philo, pthread_t *philo_thread)
{
	pthread_create_func(cond, philo, philo_thread);
	pthread_join_func(cond, philo_thread);
}
