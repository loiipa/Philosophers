/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:28:29 by cjang             #+#    #+#             */
/*   Updated: 2021/12/01 21:03:30 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_mornitor(void *p)
{
	t_philo			*philo;
	pthread_t		tid;
	int				i;
	struct timeval	middle_check;

	tid = pthread_self();
	philo = (t_philo *)p;
	i = 0;
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	while (i <= 1000)
	{
		if (time_check >= i)
		{
			printf("----- %dms -----\n", i);
			i += 100;
		}
		usleep(100);
	}
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (NULL);
}

void	*ft_thread(void *p)
{
	t_philo			*philo;
	pthread_t		tid;
	int				i;
	struct timeval	middle_check;

	tid = pthread_self();
	philo = (t_philo *)p;
	i = 0;
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	while (i < 3)
	{
		gettimeofday(&middle_check, NULL);
		time_check = (int)time_diff(&start, &middle_check);
		printf("%dms	%d	index: %d	tid: %x\n", time_check, i++, *index, (unsigned int)tid);
		usleep(100000);
	}
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	printf("fin		%d\n\n", *index);
	// 한 프로세스 안에 쓰레드가 동시에 작업을 하고 있는 것 같은 모습??
	// 그렇다면 어떻게 쓰레드를 create 한 순서대로 작동하게 만드는지
	//nutex->병렬->직렬로 연결하는 모습
	return (NULL);
}
