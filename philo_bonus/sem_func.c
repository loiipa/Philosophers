/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:08:11 by cjang             #+#    #+#             */
/*   Updated: 2021/12/15 13:53:00 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	sem_open_func(unsigned int num, sem_t **sem, char *s)
{
	sem_unlink(s);
	*sem = sem_open(s, O_CREAT, 0777, num);
	if (*sem == SEM_FAILED)
		return (1);
	return (0);
}

static int	sem_destroy_func(sem_t *sem, char *s)
{
	int		check;

	check = sem_unlink(s);
	if (check != 0)
		printf("sem_unlink error\n");
	check = sem_close(sem);
	if (check != 0)
		printf("sem_close error\n");
	return (1);
}

int	init_t_sema(unsigned int num, t_sema *sema)
{
	int		check;

	check = sem_open_func(num, &sema->died_sem, "died");
	if (check != 0)
		return (1);
	check = sem_open_func(num, &sema->eat_sem, "eat");
	if (check != 0)
		return (sem_destroy_func(sema->died_sem, "died"));
	check = sem_open_func(num, &sema->fork, "fork");
	if (check != 0)
	{
		sem_destroy_func(sema->died_sem, "died");
		return (sem_destroy_func(sema->eat_sem, "eat"));
	}
	check = sem_open_func(1, &sema->print, "print");
	if (check != 0)
	{
		sem_destroy_func(sema->died_sem, "died");
		sem_destroy_func(sema->eat_sem, "eat");
		return (sem_destroy_func(sema->fork, "fork"));
	}
	return (0);
}

void	t_sema_destory_func(t_sema *sema)
{
	sem_destroy_func(sema->died_sem, "died");
	sem_destroy_func(sema->eat_sem, "eat");
	sem_destroy_func(sema->fork, "fork");
	sem_destroy_func(sema->print, "print");
}
