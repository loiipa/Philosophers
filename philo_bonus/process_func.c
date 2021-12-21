/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:21:27 by cjang             #+#    #+#             */
/*   Updated: 2021/12/21 18:56:39 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*ft_died_monitor(void *p)
{
	t_philo			*philo;
	unsigned int	time_check;
	struct timeval	cur_time;

	philo = (t_philo *)p;
	while (philo->cond->fin_flag == 0)
	{
		usleep(USLEEP_TIME);
		gettimeofday(&cur_time, NULL);
		time_check = (int)time_diff(&philo->eat_time, &cur_time);
		if (time_check >= philo->cond->time_to_die)
		{
			philo->cond->fin_flag = 1;
			sem_wait(philo->cond->print_sem);
			time_check = (int)time_diff(&philo->cond->start_time, &cur_time);
			printf("%d %d died\n", time_check, philo->index);
			sem_post(philo->cond->died_sem);
			// sem_post(philo->cond->print_sem);
		}
	}
	return (NULL);
}

void	process_init(t_cond *c, t_philo *p, pid_t *pid)
{
	unsigned int	i;
	int				check;
	pthread_t		died_check;

	i = 0;
	while (i < c->num_of_philo)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			sem_wait(c->died_sem);
			sem_wait(c->eat_sem);
			check = pthread_create(&died_check, NULL, ft_died_monitor, (void *)&p[i]);
			if (check != 0)
			{
				printf("pthread_create error\n");
				c->fin_flag = 1;
				c->return_value = 1;
				c->pthread_success = i;
				return ;
			}
			ft_philo_process(&p[i]);
			check = pthread_join(died_check, NULL);
			if (check != 0)
			{
				printf("pthread_join error\n");
				c->fin_flag = 1;
				c->return_value = 1;
			}
			exit(0);
		}
		i++;
	}
	c->pthread_success = i;
}
