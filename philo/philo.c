/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:20:15 by cjang             #+#    #+#             */
/*   Updated: 2021/12/24 22:49:14 by cjang            ###   ########.fr       */
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

static void	died_func(t_cond *cond, t_philo *philo, int i)
{
	unsigned int	time_check;
	struct timeval	cur_time;

	cond->fin_flag = 1;
	pthread_mutex_lock(&cond->print_mutex);
	gettimeofday(&cur_time, NULL);
	time_check = (int)time_diff(&cond->start_time, &cur_time);
	printf("%d %d died\n", time_check, philo[i].index);
	pthread_mutex_unlock(&cond->print_mutex);
}

static void	ft_monitor(t_cond *cond, t_philo *philo)
{
	unsigned int	i;
	unsigned int	time_check;
	struct timeval	cur_time;

	while (cond->fin_flag == 0)
	{
		usleep(USLEEP_TIME);
		i = 0;
		while (cond->fin_flag == 0 && i < cond->num_of_philo)
		{
			gettimeofday(&cur_time, NULL);
			time_check = (int)time_diff(&philo[i].eat_time, &cur_time);
			if (philo->eat_fin_flag == 0 && time_check >= cond->time_to_die)
				died_func(cond, philo, i);
			i++;
		}
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
	if (mutex_init(&philo_cond, fork) == 1)
	{
		free_func(&philo, &philo_thread, &fork);
		return (print_return ("mutex_init_fail", 1));
	}
	init_t_philo(&philo_cond, philo, fork);
	pthread_create_func(&philo_cond, philo, philo_thread);
	ft_monitor(&philo_cond, philo);
	pthread_join_func(philo_cond.pthread_success, &philo_cond, philo_thread);
	mutex_destroy(&philo_cond, fork);
	free_func(&philo, &philo_thread, &fork);
	return (philo->cond->return_value);
}
