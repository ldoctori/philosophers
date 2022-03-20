/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:13:37 by ldoctori          #+#    #+#             */
/*   Updated: 2022/03/19 19:13:41 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_list_init_helper(t_philo *philo, t_input *input, int id)
{
	philo->input = input;
	philo->number_of_meal = 0;
	philo->eat_state = 0;
	philo->time_of_last_meal = 0;
	philo->philo_id = id;
}

t_philo	*philo_list_init(t_input *input)
{
	int		i;
	t_philo	*philo;
	t_philo	*tmp;
	t_philo	*start;

	philo = malloc(sizeof(t_philo));
	philo_list_init_helper(philo, input, 1);
	start = philo;
	i = 2;
	while (i <= input->philo_num)
	{
		tmp = malloc(sizeof(t_philo));
		philo->next = tmp;
		philo = philo->next;
		philo_list_init_helper(philo, input, i);
		i++;
	}
	philo->next = start;
	return (start);
}

t_mutex	*mtx_list_init(int number)
{
	int		i;
	t_mutex	*mtx;
	t_mutex	*start;

	mtx = malloc(sizeof(t_mutex));
	pthread_mutex_init(&mtx->mutex, NULL);
	start = mtx;
	i = 1;
	while (i < number)
	{
		mtx->next = malloc(sizeof(t_mutex));
		mtx->next->prev = mtx;
		mtx = mtx->next;
		pthread_mutex_init(&mtx->mutex, NULL);
		i++;
	}
	mtx->next = start;
	start->prev = mtx;
	return (start);
}

void	philo_mtx_accordance(t_philo *philo, t_mutex *mtx,
		struct timeval *tv, pthread_mutex_t *dead)
{
	philo->left = mtx;
	philo->right = mtx->prev;
	philo->time_of_start_sec = tv->tv_sec;
	philo->time_of_start_usec = tv->tv_usec;
	philo->dead = dead;
	philo = philo->next;
	mtx = mtx->next;
	while (philo->philo_id != 1)
	{
		philo->left = mtx;
		philo->right = mtx->prev;
		philo->time_of_start_sec = tv->tv_sec;
		philo->time_of_start_usec = tv->tv_usec;
		philo->dead = dead;
		philo = philo->next;
		mtx = mtx->next;
	}
}
