/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:08:08 by cjang             #+#    #+#             */
/*   Updated: 2021/12/11 14:44:44 by cjang            ###   ########.fr       */
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
			c->fin_flag = 1;
			c->return_value = 1;
			c->pthread_success = i;
			return ;
		}
		i++;
	}
	c->pthread_success = i;
}

void	pthread_join_func(unsigned int num, t_cond *c, pthread_t *p_t)
{
	unsigned int	i;
	int				check;

	i = 0;
	while (i < num)
	{
		check = pthread_join(p_t[i], NULL);
		if (check != 0)
		{
			printf("pthread_join error\n");
			c->fin_flag = 1;
			c->return_value = 1;
			return ;
		}
		i++;
	}
}
