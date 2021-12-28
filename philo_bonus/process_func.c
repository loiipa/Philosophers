/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:21:27 by cjang             #+#    #+#             */
/*   Updated: 2021/12/28 15:22:52 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*ft_d_monitor(void *p)
{
	t_philo			*philo;
	long long		time_check;
	struct timeval	cur_time;

	philo = (t_philo *)p;
	usleep(USLEEP_TIME);
	while (philo->cond->fin_flag == 0)
	{
		gettimeofday(&cur_time, NULL);
		time_check = time_diff(&philo->eat_time, &cur_time);
		if (time_check >= philo->cond->time_to_die)
		{
			philo->cond->fin_flag = 1;
			sem_wait(philo->cond->print_sem);
			gettimeofday(&cur_time, NULL);
			time_check = time_diff(&philo->cond->start_time, &cur_time);
			printf("%lld %d died\n", time_check, philo->index);
			sem_post(philo->cond->died_sem);
		}
		else if (time_check + 4 < philo->cond->time_to_die)
			usleep((philo->cond->time_to_die - time_check) * 900);
		else
			usleep(USLEEP_TIME);
	}
	return (NULL);
}

static void	pthread_error_check(t_cond *c, int check, char *s)
{
	int		i;

	if (check == 0)
		return ;
	i = 0;
	printf("%s\n", s);
	c->fin_flag = 1;
	sem_post(c->died_sem);
	sem_wait(c->print_sem);
	exit(1);
}

static void	fork_error(pid_t *pid, int len)
{
	int		i;

	printf("fork error\n");
	i = 0;
	while (i < len)
		kill(pid[i++], SIGINT);
	exit(1);
}

void	process_init(t_cond *c, t_philo *p, pid_t *pid)
{
	unsigned int	i;
	int				check;
	pthread_t		d_check;

	i = 0;
	while (i < c->num_of_philo)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			sem_wait(c->died_sem);
			sem_wait(c->eat_sem);
			check = pthread_create(&d_check, NULL, ft_d_monitor, (void *)&p[i]);
			pthread_error_check(c, check, "pthread_create error");
			ft_philo_process(&p[i]);
			check = pthread_join(d_check, NULL);
			pthread_error_check(c, check, "pthread_join error");
			exit(0);
		}
		else if (pid[i] < 0)
			fork_error(pid, i);
		i++;
	}
}
