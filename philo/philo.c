/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:20:15 by cjang             #+#    #+#             */
/*   Updated: 2021/12/06 15:34:55 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	argv_check(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
		if (ft_atoi(argv[i++]) <= 0)
			return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cond			philo_cond;
	t_philo			*philo;
	pthread_t		*philo_thread;
	pthread_mutex_t	*fork;

	if (!(argc == 5 || argc == 6))
		return (print_return("Wrong number of arguments", 1));
	if (argv_check(argc, argv) == 1)
		return (print_return("Invalid argument", 1));
	init_t_cond(&philo_cond, argc, argv);
	if (malloc_func(&philo, &philo_thread, &fork, philo_cond.num_of_philo) == 1)
		return (print_return("malloc fail", 1));
	mutex_init(&philo_cond, fork);
	init_t_philo(&philo_cond, philo, fork);
	pthread_func(&philo_cond, philo, philo_thread);
	mutex_destroy(&philo_cond, fork);
	free_func(&philo, &philo_thread, &fork);
}

//밀리초		1s / 1,000
//마이크로초	 1s / 1,000,000
// 총체적으로 밥을 다먹은 철학자, 자는 철학자 등을 모니터하는 상황은 어떻게 만들지?
// 비정상 종료시 보조 스레드들의 자원 반환은 같이 이루어져야 하는게 아닐까..?
