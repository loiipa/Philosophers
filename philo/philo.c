/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:20:15 by cjang             #+#    #+#             */
/*   Updated: 2021/12/08 17:41:45 by cjang            ###   ########.fr       */
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

static void	ft_monitor(t_cond *cond)
{
	while (cond->fin_flag == 0)
	{
		usleep(USLEEP_TIME);
		if (cond->philo_eat_fin_count == cond->num_of_philo)
			cond->fin_flag = 1;
	}
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
	pthread_create_func(&philo_cond, philo, philo_thread);
	ft_monitor(&philo_cond);
	pthread_join_func(&philo_cond, philo_thread);
	mutex_destroy(&philo_cond, fork);
	free_func(&philo, &philo_thread, &fork);
}
