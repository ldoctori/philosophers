/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:05:50 by ldoctori          #+#    #+#             */
/*   Updated: 2022/04/03 16:05:55 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_some(t_philo *philo, char *str)
{
	int	time;

	time = get_time(philo);
	if (*philo->if_someone_dead != 1)
	{
		pthread_mutex_lock(philo->write);
		printf("%i philosopher %i %s\n", time, philo->philo_id, str);
		pthread_mutex_unlock(philo->write);
	}
}

void	sleep_time(t_philo *philo, int time)
{
	if (*philo->if_someone_dead != 1)
		usleep(time * 1000);
}

void	eating(t_philo *philo)
{
	gettimeofday(&philo->tv, NULL);
	philo->time_of_last_meal = (philo->tv.tv_sec
			- philo->time_of_start_sec) * 1000
		+ (philo->tv.tv_usec - philo->time_of_start_usec) / 1000;
	philo->eat_state = 1;
	print_some(philo, "is eating");
	while ((philo->tv.tv_sec - philo->time_of_start_sec) * 1000
		+ (philo->tv.tv_usec - philo->time_of_start_usec) / 1000
		- philo->time_of_last_meal < philo->input->time_to_eat)
	{
		if (*philo->if_someone_dead == 1)
			break ;
		gettimeofday(&philo->tv, NULL);
	}
	pthread_mutex_unlock(&philo->left->mutex);
	pthread_mutex_unlock(&philo->right->mutex);
	philo->number_of_meal++;
	philo->eat_state = 0;
}

void	*print(void *ph)
{
	t_philo	*philo;

	if (!ph)
		return (NULL);
	philo = ph;
	while (*philo->if_someone_dead != 1)
	{
		pthread_mutex_lock(&philo->right->mutex);
		print_some(philo, "has taken fork");
		if (philo->right == philo->left)
		{
			usleep(philo->input->time_to_die * 1000);
			return (NULL);
		}
		pthread_mutex_lock(&philo->left->mutex);
		print_some(philo, "has taken fork");
		eating(philo);
		if (philo->number_of_meal == philo->input->max_number_of_meal)
			return (NULL);
		print_some(philo, "is sleeping");
		sleep_time(philo, philo->input->time_to_sleep);
		print_some(philo, "is thinking");
	}
	return (NULL);
}
