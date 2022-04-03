/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:13:37 by ldoctori          #+#    #+#             */
/*   Updated: 2022/04/03 16:15:04 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_sems	*semofors_init(int philo_num)
{
	t_sems	*sems;

	sems = malloc(sizeof(t_sems));
	sem_unlink("/forks");
	sem_unlink("/write");
	sems->forks = sem_open("/forks", O_CREAT, 0644, philo_num);
	sems->write = sem_open("/write", O_CREAT, 0644, 1);
	return (sems);
}

void	philo_list_init_helper(t_philo *philo, t_input *input,
			t_sems *sems, struct timeval *tv)
{
	philo->input = input;
	philo->number_of_meal = 0;
	philo->eat_state = 0;
	philo->time_of_last_meal = 0;
	philo->sems = sems;
	philo->time_of_start_sec = tv->tv_sec;
	philo->time_of_start_usec = tv->tv_usec;
}

t_philo	*philo_list_init(t_input *input, t_sems *sems, struct timeval *tv)
{
	int		i;
	t_philo	*philo;
	t_philo	*tmp;
	t_philo	*start;

	philo = malloc(sizeof(t_philo));
	philo_list_init_helper(philo, input, sems, tv);
	philo->philo_id = 1;
	start = philo;
	i = 2;
	while (i <= input->philo_num)
	{
		tmp = malloc(sizeof(t_philo));
		philo->next = tmp;
		philo = philo->next;
		philo_list_init_helper(philo, input, sems, tv);
		philo->philo_id = i;
		i++;
	}
	philo->next = start;
	return (start);
}
