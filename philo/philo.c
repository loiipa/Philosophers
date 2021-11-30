/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:20:15 by cjang             #+#    #+#             */
/*   Updated: 2021/11/26 20:54:36 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t		mutex_lock[2];
struct timeval		start;
int					time_check = 0;

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

float	time_diff(struct timeval *start, struct timeval *end)
{
	float	sec_to_msec;
	float	usec_to_msec;

	sec_to_msec = 1e+3 * (end->tv_sec - start->tv_sec);
	usec_to_msec = 1e-3 * (end->tv_usec - start->tv_usec);
	return (sec_to_msec + usec_to_msec);
}

void	*ft_mornitor(void *num)
{
	int				*index;
	pthread_t		tid;
	int				i;
	struct timeval	middle_check;

	tid = pthread_self();
	index = (int *)num;
	i = 0;
	pthread_mutex_lock(&mutex_lock[0]);
	while (i <= 1000)
	{
		if (time_check >= i)
		{
			printf("----- %dms -----\n", i);
			i += 100;
		}
		usleep(100);
	}
	pthread_mutex_unlock(&mutex_lock[0]);
	return (NULL);
}

void	*ft_thread(void *num)
{
	int				*index;
	pthread_t		tid;
	int				i;
	struct timeval	middle_check;

	tid = pthread_self();
	index = (int *)num;
	i = 0;
	pthread_mutex_lock(&mutex_lock[1]);
	while (i < 3)
	{
		gettimeofday(&middle_check, NULL);
		time_check = (int)time_diff(&start, &middle_check);
		printf("%dms	%d	index: %d	tid: %x\n", time_check, i++, *index, (unsigned int)tid);
		usleep(100000);
	}
	pthread_mutex_unlock(&mutex_lock[1]);
	printf("fin		%d\n\n", *index);
	// 한 프로세스 안에 쓰레드가 동시에 작업을 하고 있는 것 같은 모습??
	// 그렇다면 어떻게 쓰레드를 create 한 순서대로 작동하게 만드는지
	//nutex->병렬->직렬로 연결하는 모습
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo		philo_info;
	pthread_t	philo_thread[6];
	int			index[6];
	int			i;
	int			check;
	struct timeval	end;

	// if (!(argc == 5 || argc == 6))
	// {
	// 	printf("Wrong number of arguments\n");
	// 	return (1);
	// }
	/* check_argv(argv); -> argv가 유효한 '숫자'인지 체크 */

	// init_t_philo(&philo_info, argc, argv);

	/* init_philo(philo.num_of_philo); -> 철학자 각각의 thread 만들어주기 */
	gettimeofday(&start, NULL);
	i = 0;
	while (i < 6)
	{
		index[i] = i;
		i++;
	}
	pthread_mutex_init(&mutex_lock[0], NULL);
	pthread_mutex_init(&mutex_lock[1], NULL);
	i = 0;
	while (i < 6)
	{
		if (i == 0)
			check = pthread_create(&philo_thread[i], NULL, ft_mornitor, (void *)&index[i]);
		else
			check = pthread_create(&philo_thread[i], NULL, ft_thread, (void *)&index[i]);
		if (check != 0)
		{
			printf("pthread_create error\n");
			return (1);
		}
		i++;
	}
	i = 0;
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
	pthread_mutex_destroy(&mutex_lock[0]);
	pthread_mutex_destroy(&mutex_lock[1]);
	gettimeofday(&end, NULL);
	printf("time - %0.8f\n", time_diff(&start, &end));
	return (0);
}

//밀리초		1s / 1,000
//마이크로초	 1s / 1,000,000
// 총체적으로 밥을 다먹은 철학자, 자는 철학자 등을 모니터하는 상황은 어떻게 만들지?
// 비정상 종료시 보조 스레드들의 자원 반환은 같이 이루어져야 하는게 아닐까..?
