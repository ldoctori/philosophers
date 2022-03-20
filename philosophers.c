/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:27:26 by ldoctori          #+#    #+#             */
/*   Updated: 2022/03/19 19:27:34 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *ph)
{
	t_philo	*philo;

	philo = ph;
	while (1)
	{
		if (philo->philo_id == philo->input->philo_num
			&& philo->input->max_number_of_meal > 0
			&& philo->number_of_meal >= philo->input->max_number_of_meal)
			return (NULL);
		if (die_check(philo) == 1 && philo->eat_state == 0)
		{
			pthread_mutex_lock(philo->dead);
			printf("%i philosopher %i died\n", get_time(philo), philo->philo_id);
			return (NULL);
		}
		philo = philo->next;
	}
}

void	*print(void *ph)
{
	t_philo	*philo;

	if (!ph)
		return (NULL);
	philo = ph;
	pthread_mutex_lock(&philo->right->mutex);
	pthread_mutex_lock(philo->dead);
	printf("%i philosopher %i has taken right fork\n",
		get_time(philo), philo->philo_id);
	pthread_mutex_unlock(philo->dead);
	if (philo->left != philo->right)
		pthread_mutex_lock(&philo->left->mutex);
	else
		usleep(philo->input->time_to_die * 1000);
	if (die_check(philo) == 1)
	{
		pthread_mutex_unlock(&philo->right->mutex);
		pthread_mutex_unlock(&philo->left->mutex);
		printf("%i philosopher %i died\n", get_time(philo), philo->philo_id);
		return (NULL);
	}
	pthread_mutex_lock(philo->dead);
	printf("%i philosopher %i has taken left fork\n",
		get_time(philo), philo->philo_id);
	printf("%i philosopher %i is eating\n", get_time(philo), philo->philo_id);
	pthread_mutex_unlock(philo->dead);
	philo->number_of_meal++;
	philo->eat_state = 1;
	usleep(philo->input->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->right->mutex);
	pthread_mutex_unlock(&philo->left->mutex);
	gettimeofday(&philo->tv, NULL);
	philo->time_of_last_meal = (philo->tv.tv_sec
			- philo->time_of_start_sec) * 1000
		+ (philo->tv.tv_usec - philo->time_of_start_usec) / 1000;
	philo->eat_state = 0;
	if (philo->input->max_number_of_meal > 0
		&& philo->number_of_meal >= philo->input->max_number_of_meal)
		return (NULL);
	pthread_mutex_lock(philo->dead);
	printf("%i philosopher %i is sleeping\n", get_time(philo), philo->philo_id);
	pthread_mutex_unlock(philo->dead);
	usleep(philo->input->time_to_sleep * 1000);
	pthread_mutex_lock(philo->dead);
	printf("%i philosopher %i is thinking\n", get_time(philo), philo->philo_id);
	pthread_mutex_unlock(philo->dead);
	return (print(ph));
}

void main_helper(pthread_t **arr, t_philo *philo, t_mutex *mtx)
{
	pthread_t	mon;
	int			i;
	int			philo_num;

	philo_num = philo->input->philo_num;
	i = 0;
	gettimeofday(&tv, NULL);
	philo_mtx_accordance(philo, mtx, &tv, dead);
	while (i < input.philo_num)
	{
		pthread_create(arr[i], NULL, print, (void *) philo);
		pthread_detach(*arr[i]);
		philo = philo->next;
		i++;
		usleep(100);
	}
	pthread_create(&mon, NULL, monitor, (void *) philo);
	pthread_join(mon, NULL);
	pthread_mutex_destroy(philo->dead);
	free(philo->dead);
	free_philo(philo);
	free_destroy_mtx(mtx, philo_num);
	free_thread_arr(arr, philo_num);
}

int	main(int argc, char **argv)
{
	pthread_t		**arr;
	t_philo			*philo;
	t_mutex			*mtx;
	t_input			input;
	struct timeval	tv;
	pthread_mutex_t	*dead;

	dead = malloc(sizeof(t_mutex));
	pthread_mutex_init(dead, NULL);
	if (argc < 5 || argc > 6)
		return (0);
	take_input(&input, ++argv);
	arr = arr_create(input.philo_num);
	philo = philo_list_init(&input);
	mtx = mtx_list_init(input.philo_num);

	gettimeofday(&tv, NULL);
	philo_mtx_accordance(philo, mtx, &tv, dead);
	main_helper(arr, philo, mtx);
/*	while (i < input.philo_num)
	{
		pthread_create(arr[i], NULL, print, (void *) philo);
		philo = philo->next;
		i++;
		usleep(100);
	}

	pthread_create(&mon, NULL, monitor, (void *) philo);
	i = 0;
	while (i < input.philo_num)
	{
		pthread_detach(*arr[i]);
		i++;
	}
	pthread_join(mon, NULL);
	pthread_mutex_destroy(dead);
	free(dead);
	free_philo(philo);
	free_destroy_mtx(mtx, input.philo_num);
	free_thread_arr(arr, input.philo_num);*/
}
