/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:26:34 by ldoctori          #+#    #+#             */
/*   Updated: 2022/04/03 16:26:36 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>           
# include <sys/stat.h>        
# include <semaphore.h>
# include <signal.h>

typedef struct s_input
{
	int		philo_num;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		max_number_of_meal;
}	t_input;

typedef struct s_sems
{
	sem_t	*forks;
	sem_t	*write;
}	t_sems;

typedef struct s_philo
{
	struct s_philo	*next;
	int				*if_someone_dead;
	int				time_of_last_meal;
	int				time_of_start_sec;
	int				time_of_start_usec;
	int				philo_id;
	int				number_of_meal;
	int				eat_state;
	struct timeval	tv;
	t_input			*input;
	t_sems			*sems;
}	t_philo;

int			ft_atoi(const char *str);
t_sems		*semofors_init(int philo_num);
t_philo		*philo_list_init(t_input *input, t_sems *sems, struct timeval *tv);
void		take_input(t_input *input, char **argv);
pthread_t	**arr_create(int philo_num);
int			die_check(t_philo *philo);
int			get_time(t_philo *philo);
void		free_philo(t_philo *philo);
void		print(t_philo *philo);

#endif
