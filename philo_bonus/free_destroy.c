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

#include "philo_bonus.h"

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
