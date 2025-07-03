/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:47:58 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/27 16:00:33 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	philo_routine_aux(t_philo *philo)
{
	int	fork_acquisition_status;

	if (philo_is_sim_over(philo))
		return (1);
	fork_acquisition_status = philo_take_forks_ordered(philo);
	if (fork_acquisition_status == 1)
		return (1);
	if (philo_is_sim_over(philo))
	{
		philo_release_forks(philo);
		return (1);
	}
	philo_eat(philo);
	if (philo_is_sim_over(philo))
		return (1);
	philo_sleep(philo);
	if (philo_is_sim_over(philo))
		return (1);
	philo_think(philo);
	return (0);
}

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
	if (philo->num_of_philos == 1)
	{
		philo_usleep(philo, 1);
	}
	else if (philo->id % 2 != 0)
	{
		philo_think(philo);
		philo_usleep(philo, 1);
	}
	while (true)
	{
		if (philo_routine_aux(philo))
			break ;
	}
	return (NULL);
}
