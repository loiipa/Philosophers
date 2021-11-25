/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:20:15 by cjang             #+#    #+#             */
/*   Updated: 2021/11/25 20:57:23 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_t_philo(t_philo *philo, int argc, char **argv)
{
	philo->num_of_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->limit_num_of_eat = ft_atoi(argv[5]);
	else
		philo->limit_num_of_eat = 0;
}

void	*ft_thread(void *num)
{
	int			*index;
	pthread_t	tid;

	tid = pthread_self();
	index = (int *)num;
	printf("index: %d, tid: %x\n", *index, (unsigned int)tid);
	sleep(1);
}

int	main(int argc, char **argv)
{
	t_philo		philo_info;
	pthread_t	philo_thread[6];
	int			i;

	// if (!(argc == 5 || argc == 6))
	// {
	// 	printf("Wrong number of arguments\n");
	// 	retrun (1);
	// }
	// check_argv(argv); -> argv가 유효한 '숫자'인지 체크
	// init_t_philo(&philo_info, argc, argv);
	// init_philo(philo.num_of_philo); -> 철학자 각각의 thread 만들어주기
	i = 1;
	while (i < 6)
	{
		pthread_create(&philo_thread[i], NULL, ft_thread, (void *)&i);
		i++;

	}
	i = 1;
	while (i < 6)
	{
		pthread_join(philo_thread[i], NULL);
		i++;
	}
	return (0);
}
