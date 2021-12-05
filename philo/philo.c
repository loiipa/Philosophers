/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:20:15 by cjang             #+#    #+#             */
/*   Updated: 2021/12/05 18:06:53 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_func(t_cond *c, t_philo *p, pthread_mutex_t *f)
{
	int		i;

	i = 0;
	while (i < c->num_of_philo)
	{
		pthread_mutex_init(&f[i], NULL);
		i++;
	}
	i = 0;
	while (i < c->num_of_philo)
	{
		init_t_philo(&p[i], i + 1, &f[i], &f[(i + 1) % c->num_of_philo]);
		init_t_philo_2(&p[i], c);
		i++;
	}
}

static void	pthread_create_func(t_cond *c, t_philo *p, pthread_t *p_t)
{
	int		i;
	int		check;
	void	(*fp)();

	i = 0;
	while (i < c->num_of_philo * 2)
	{
		if (i % 2 == 0)
			fp = (void *)ft_thread;
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
	int		i;
	int		check;

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

static void	mutex_destroy_func(t_cond *cond, pthread_mutex_t *fork)
{
	int		i;

	i = 0;
	while (i <= cond->num_of_philo)
	{
		pthread_mutex_destroy(&fork[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_cond			philo_cond;
	t_philo			philo[THREAD_NUM];
	pthread_t		philo_thread[THREAD_NUM * 2];
	pthread_mutex_t	fork[THREAD_NUM];

	if (!(argc == 5 || argc == 6))
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	if (init_t_cond(&philo_cond, argc, argv) == 1)
	{
		printf("Invalid unargument\n");
		return (1);
	}
	init_func(&philo_cond, philo, fork);
	pthread_create_func(&philo_cond, philo, philo_thread);
	pthread_join_func(&philo_cond, philo_thread);
	mutex_destroy_func(&philo_cond, fork);
}

//밀리초		1s / 1,000
//마이크로초	 1s / 1,000,000
// 총체적으로 밥을 다먹은 철학자, 자는 철학자 등을 모니터하는 상황은 어떻게 만들지?
// 비정상 종료시 보조 스레드들의 자원 반환은 같이 이루어져야 하는게 아닐까..?
