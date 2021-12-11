/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:21:27 by cjang             #+#    #+#             */
/*   Updated: 2021/12/11 18:38:14 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	process_init(t_cond *c, t_philo *p, pid_t *pid)
{
	unsigned int	i;

	i = 0;
	while (i < c->num_of_philo)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			sem_wait(c->died_sem);
			sem_wait(c->eat_sem);
			ft_philo_process(&p[i]);
			exit(0);
		}
		i++;
	}
}
