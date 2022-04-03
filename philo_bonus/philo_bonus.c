/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:21:52 by ldoctori          #+#    #+#             */
/*   Updated: 2022/04/03 16:21:53 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	pid_wait(t_philo *philo, int *philo_procs)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	j = -1;
	ret = 0;
	while (i < philo->input->philo_num)
	{
		waitpid(philo_procs[i], &ret, 0);
		if (ret != 0)
		{
			while (++j < philo->input->philo_num)
				kill(philo_procs[j], SIGKILL);
			break ;
		}
		i++;
	}
	sem_close(philo->sems->forks);
	sem_close(philo->sems->write);
	sem_unlink("/forks");
	sem_unlink("/write");
	free(philo_procs);
}

void	philo_proc_launcher(t_philo *philo)
{
	int	i;
	int	*philo_procs;
	int	if_someone_dead;

	i = 0;
	philo_procs = malloc(sizeof(int) * philo->input->philo_num);
	if_someone_dead = 0;
	while (i < philo->input->philo_num)
	{	
		philo->if_someone_dead = &if_someone_dead;
		philo_procs[i] = fork();
		if (philo_procs[i] < 0)
			return ;
		if (philo_procs[i] == 0)
		{
			print(philo);
			break ;
		}
		i++;
		philo = philo->next;
		usleep(100);
	}
	pid_wait(philo, philo_procs);
	return ;
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_input			input;
	t_sems			*sems;
	struct timeval	tv;

	if (argc < 5 || argc > 6)
		return (0);
	take_input(&input, ++argv);
	sems = semofors_init(input.philo_num);
	gettimeofday(&tv, NULL);
	philo = philo_list_init(&input, sems, &tv);
	philo_proc_launcher(philo);
	free(sems);
	free_philo(philo);
}
