/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:10:43 by cjang             #+#    #+#             */
/*   Updated: 2021/12/22 09:39:01 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_mutex_destory(t_cond *cond)
{
	int				check;

	check = pthread_mutex_destroy(&cond->print_mutex);
	if (check != 0)
	{
		cond->return_value = 1;
		printf("mutex_destrtoy error - print_mutex\n");
	}
}

static void	fork_mutex_destroy(unsigned int num, t_cond *c, pthread_mutex_t *f)
{
	unsigned int	i;
	int				check;

	i = 0;
	while (i < num)
	{
		check = pthread_mutex_destroy(&f[i]);
		if (check != 0)
		{
			c->return_value = 1;
			printf("mutex_destrtoy error - fork[%d]\n", i);
		}
		i++;
	}
}

int	mutex_init(t_cond *cond, pthread_mutex_t *fork)
{
	int				i;
	int				check;

	i = 0;
	check = pthread_mutex_init(&cond->print_mutex, NULL);
	if (check != 0)
		return (1);
	while ((unsigned int)i < cond->num_of_philo)
	{
		check = pthread_mutex_init(&fork[i], NULL);
		if (check != 0)
		{
			cond->fin_flag = 1;
			print_mutex_destory(cond);
			fork_mutex_destroy(i, cond, fork);
			return (1);
		}
		i++;
	}
	return (0);
}

void	mutex_destroy(t_cond *cond, pthread_mutex_t *fork)
{
	print_mutex_destory(cond);
	fork_mutex_destroy(cond->num_of_philo, cond, fork);
}

void	*mutex_unlock(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
	return (NULL);
}
