/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:47:58 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/01 00:20:42 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief The main function executed by each philosopher thread.
 *        Manages the eat-sleep-think lifecycle.
 * @param arg A void pointer to the philosopher's t_philo structure.
 * @return void* Always returns NULL.
 */
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		ft_usleep(1);
	while (!philo_is_sim_over(philo))
	{
		philo_take_forks_ordered(philo);
		if (philo_is_sim_over(philo) || philo->num_of_philos == 1)
		{
			break ;
		}
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
