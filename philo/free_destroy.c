/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:50:38 by ldoctori          #+#    #+#             */
/*   Updated: 2022/03/19 18:50:56 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_philo *philo)
{
	t_philo	*tmp;
	int		i;
	int		num;

	num = philo->input->philo_num;
	i = 0;
	while (i < num)
	{
		tmp = philo;
		philo = philo->next;
		free(tmp);
		i++;
	}
}

void	free_destroy_mtx(t_mutex *mtx, int num)
{
	t_mutex	*tmp;
	int		i;

	i = 0;
	while (i < num)
	{
		tmp = mtx;
		mtx = mtx->next;
		pthread_mutex_destroy(&tmp->mutex);
		free(tmp);
		i++;
	}
}

void	free_thread_arr(pthread_t **arr, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
