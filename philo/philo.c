/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:27:26 by ldoctori          #+#    #+#             */
/*   Updated: 2022/04/03 16:07:29 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *ph)
{
	t_philo	*philo;
	int		time;
	int		die;

	philo = ph;
	while (1)
	{
		die = die_check(philo);
		if (die == 1 && philo->eat_state == 0)
		{	
			time = get_time(philo);
			*philo->if_someone_dead = 1;
			pthread_mutex_lock(philo->write);
			printf("%i philosopher %i died\n", time, philo->philo_id);
			return (NULL);
		}
		else if (philo->philo_id == philo->input->philo_num
			&& philo->input->max_number_of_meal > 0
			&& philo->number_of_meal >= philo->input->max_number_of_meal)
			return (NULL);
		philo = philo->next;
	}
}

void	threads_wait(t_philo *philo, t_mutex *mtx, pthread_t **arr)
{
	int	i;
	int	philo_num;

	i = 0;
	philo_num = philo->input->philo_num;
	while (i < philo_num)
	{
		pthread_join(*arr[i], NULL);
		philo = philo->next;
		i++;
	}
	pthread_mutex_destroy(philo->write);
	free(philo->write);
	free_philo(philo);
	free_destroy_mtx(mtx, philo_num);
	free_thread_arr(arr, philo_num);
}

void	threads_launcher(t_philo *philo, t_mutex *mtx)
{
	int			i;
	int			philo_num;
	int			if_someone_dead;
	pthread_t	**arr;

	arr = arr_create(philo->input->philo_num);
	if_someone_dead = 0;
	philo_num = philo->input->philo_num;
	i = 0;
	while (i < philo_num)
	{
		philo->if_someone_dead = &if_someone_dead;
		pthread_create(arr[i], NULL, print, (void *) philo);
		philo = philo->next;
		i++;
		usleep(100);
	}
	monitor((void *)philo);
	threads_wait(philo, mtx, arr);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_mutex			*mtx;
	t_input			input;
	struct timeval	tv;
	pthread_mutex_t	*write;

	if (argc < 5 || argc > 6)
		return (0);
	write = malloc(sizeof(t_mutex));
	pthread_mutex_init(write, NULL);
	take_input(&input, ++argv);
	philo = philo_list_init(&input);
	mtx = mtx_list_init(input.philo_num);
	gettimeofday(&tv, NULL);
	philo_mtx_accordance(philo, mtx, &tv, write);
	threads_launcher(philo, mtx);
}
