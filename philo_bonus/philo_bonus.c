/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:20:15 by cjang             #+#    #+#             */
/*   Updated: 2021/12/11 21:28:35 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	argv_check(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
		if (ft_atoi(argv[i++]) <= 0)
			return (1);
	return (0);
}

static void	*ft_eat_monitor(void *p)
{
	unsigned int	i;
	t_cond			*cond;

	cond = (t_cond *)p;
	i = 0;
	while (i < cond->num_of_philo)
	{
		sem_wait(cond->eat_sem);
		i++;
	}
	sem_post(cond->died_sem);
	return (NULL);
}

static void	ft_monitor(t_cond *cond, pid_t *pid)
{
	unsigned int	i;
	int				check;
	pthread_t		eat_check;

	usleep(1000);
	check = pthread_create(&eat_check, NULL, ft_eat_monitor, (void *)cond);
	if (check != 0)
	{
		printf("pthread_create error\n");
		return ;
	}
	sem_wait(cond->died_sem);
	i = 0;
	while (i < cond->num_of_philo)
		kill(pid[i++], SIGINT);
	i = 0;
	while (i++ <= cond->num_of_philo)
		sem_post(cond->eat_sem);
	check = pthread_join(eat_check, NULL);
	if (check != 0)
	{
		printf("pthread_detach error\n");
		return ;
	}
}

int	main(int argc, char **argv)
{
	t_cond			philo_cond;
	t_philo			*philo;
	pid_t			*philo_process;
	t_sema			sema;

	if (!(argc == 5 || argc == 6))
		return (print_return("Wrong number of arguments\n", 1));
	if (argv_check(argc, argv) == 1)
		return (print_return("Invalid argument\n", 1));
	if (init_t_sema(ft_atoi(argv[1]), &sema) == 1)
		return (print_return("sem_open failed\n", 1));
	init_t_cond(&philo_cond, &sema, argc, argv);
	if (malloc_func(&philo, &philo_process, philo_cond.num_of_philo) == 1)
		return (print_return("malloc fail\n", 1));
	init_t_philo(&philo_cond, philo, &sema);
	process_init(&philo_cond, philo, philo_process);
	ft_monitor(&philo_cond, philo_process);
	t_sema_destory_func(&sema);
	free_func(&philo, &philo_process);
	return (philo->cond->return_value);
}
