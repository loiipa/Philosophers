/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:21:08 by cjang             #+#    #+#             */
/*   Updated: 2021/12/16 22:55:03 by cjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define USLEEP_TIME 100

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_sema
{
	sem_t				*died_sem;
	sem_t				*eat_sem;
	sem_t				*fork;
	sem_t				*print;
}t_sema;

typedef struct s_cond
{
	unsigned int		num_of_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	int					limit_num_of_eat;
	sem_t				*died_sem;
	sem_t				*eat_sem;
	sem_t				*print_sem;
	int					fin_flag;
	int					return_value;
	struct timeval		start_time;
}t_cond;

typedef struct s_philo
{
	unsigned int		index;
	unsigned int		eat_conut;
	int					fin_flag;
	sem_t				*fork;
	t_cond				*cond;
	struct timeval		eat_time;
}t_philo;

int			ft_atoi(const char *str);
long long	time_diff(struct timeval *start, struct timeval *end);
void		init_t_cond(t_cond *cond, t_sema *sema, int argc, char **argv);
void		init_t_philo(t_cond *cond, t_philo *philo, t_sema *sema);
void		ft_philo_process(t_philo *philo);
int			print_return(char *s, int i);
int			malloc_func(t_philo **p, pid_t **pid, int num);
void		free_func(t_philo **p, pid_t **pid);
void		usleep_func(t_philo *philo, long long ms_time);
void		process_init(t_cond *c, t_philo *p, pid_t *pid);
int			init_t_sema(unsigned int num, t_sema *sema);
void		t_sema_destory_func(t_sema *sema);

#endif
