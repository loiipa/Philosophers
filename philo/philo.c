/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:20:15 by cjang             #+#    #+#             */
/*   Updated: 2021/12/01 21:04:38 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_cond			philo_cond;
	t_philo			philo[256];
	pthread_t		philo_thread[256];
	pthread_t		died_thread[256];
	pthread_mutex_t	fork[256];
	int				i;
	int				check;
	struct timeval	start;
	struct timeval	end;

	if (!(argc == 5 || argc == 6))
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	/* check_argv(argv); -> argv가 유효한 '숫자'인지 체크 (init에서 하든 여기서 하든) */
	init_t_cond(&philo_cond, argc, argv);
	i = 1;
	while (i <= philo_cond.num_of_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	i = 1;
	while (i <= philo_cond.num_of_philo)
	{
		init_t_philo(philo[i], i, &fork[i], &fork[(i + 1) % 5]);
		i++;
	}
	gettimeofday(&start, NULL);
	/* init_philo(philo.num_of_philo); -> 철학자 각각의 thread 만들어주기 */
	i = 1;
	while (i <= philo_cond.num_of_philo)
	{
		check = pthread_create(&philo_thread[i], NULL, ft_thread, \
		(void *)&philo[i]);
		if (check != 0)
		{
			printf("pthread_create error\n");
			return (1);
		}
		check = pthread_create(&philo_thread[i], NULL, ft_mornitor, \
		(void *)&philo[i]);
		if (check != 0)
		{
			printf("pthread_create error\n");
			return (1);
		}
		i++;
	}
	i = i;
	while (i < 6)
	{
		check = pthread_join(philo_thread[i], NULL);
		if (check != 0)
		{
			printf("pthread_join error\n");
			return (1);
		}
		i++;
	}
	i = 1;
	while (i <= philo_cond.num_of_philo)
	{
		pthread_mutex_destroy(&fork[i]);
		i++;
	}
	gettimeofday(&end, NULL);
	printf("time - %0.8f\n", time_diff(&start, &end));
	return (0);
}

//밀리초		1s / 1,000
//마이크로초	 1s / 1,000,000
// 총체적으로 밥을 다먹은 철학자, 자는 철학자 등을 모니터하는 상황은 어떻게 만들지?
// 비정상 종료시 보조 스레드들의 자원 반환은 같이 이루어져야 하는게 아닐까..?
