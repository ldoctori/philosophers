/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:55:46 by ldoctori          #+#    #+#             */
/*   Updated: 2022/03/19 18:56:44 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_input(t_input *input, char **argv)
{
	input->philo_num = ft_atoi(*argv);
	argv++;
	input->time_to_die = ft_atoi(*argv);
	argv++;
	input->time_to_eat = ft_atoi(*argv);
	argv++;
	input->time_to_sleep = ft_atoi(*argv);
	argv++;
	if (*argv != 0)
		input->max_number_of_meal = ft_atoi(*argv);
	else
		input->max_number_of_meal = -1;
}

pthread_t	**arr_create(int philo_num)
{
	pthread_t	**arr;
	int			i;

	i = 0;
	arr = malloc(sizeof(pthread_t *) * philo_num);
	while (i < philo_num)
	{
		arr[i] = malloc(sizeof(pthread_t));
		i++;
	}
	return (arr);
}

int	die_check(t_philo *philo)
{
	struct timeval	tv;
	int				passed;

	gettimeofday(&tv, NULL);
	passed = (tv.tv_sec - philo->time_of_start_sec) * 1000
		+ (tv.tv_usec - philo->time_of_start_usec) / 1000;
	if (passed - philo->time_of_last_meal >= philo->input->time_to_die)
		return (1);
	return (0);
}

int	get_time(t_philo *philo)
{
	gettimeofday(&philo->tv, NULL);
	return ((philo->tv.tv_sec - philo->time_of_start_sec) * 1000
		+ (philo->tv.tv_usec - philo->time_of_start_usec) / 1000);
}
