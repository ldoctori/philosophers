/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:16:34 by ldoctori          #+#    #+#             */
/*   Updated: 2022/04/03 16:16:36 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *ph)
{
	int		time;
	int		die;
	t_philo	*philo;

	philo = ph;
	while (1)
	{
		die = die_check(philo);
		if (die == 1 && philo->eat_state == 0)
		{	
			time = get_time(philo);
			*philo->if_someone_dead = 1;
			sem_wait(philo->sems->write);
			printf("%i philosopher %i died\n", time, philo->philo_id);
			return (NULL);
		}
		else if (philo->philo_id == philo->input->philo_num
			&& philo->input->max_number_of_meal > 0
			&& philo->number_of_meal >= philo->input->max_number_of_meal)
			return (NULL);
		usleep(100);
	}
}

void	print_some(t_philo *philo, char *str)
{
	int	time;

	time = get_time(philo);
	if (*philo->if_someone_dead != 1)
	{
		sem_wait(philo->sems->write);
		printf("%i philosopher %i %s\n", time, philo->philo_id, str);
		sem_post(philo->sems->write);
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
	sem_post(philo->sems->forks);
	sem_post(philo->sems->forks);
	philo->number_of_meal++;
	philo->eat_state = 0;
}

void	print(t_philo *philo)
{
	pthread_t	mon;

	pthread_create(&mon, NULL, monitor, (void *) philo);
	pthread_detach(mon);
	while (*philo->if_someone_dead != 1)
	{
		sem_wait(philo->sems->forks);
		print_some(philo, "has taken fork");
		if (philo == philo->next)
		{
			usleep(philo->input->time_to_die * 1000);
			exit(0);
		}
		sem_wait(philo->sems->forks);
		print_some(philo, "has taken fork");
		eating(philo);
		if (philo->number_of_meal == philo->input->max_number_of_meal)
			exit(0);
		print_some(philo, "is sleeping");
		sleep_time(philo, philo->input->time_to_sleep);
		print_some(philo, "is thinking");
	}
	exit(1);
}
