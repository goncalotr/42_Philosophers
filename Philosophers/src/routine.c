/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:47:58 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/26 17:13:00 by goteixei         ###   ########.fr       */
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
	int		fork_acquisition_status;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		philo_usleep(philo, 1);
	while (true)
	{
		if (philo_is_sim_over(philo))
			break;
		fork_acquisition_status = philo_take_forks_ordered(philo);
		if (fork_acquisition_status == 1)
			break ;
		if (philo_is_sim_over(philo))
		{
			philo_release_forks(philo);
			break ;
		}
		philo_eat(philo);
		if (philo_is_sim_over(philo))
			break;
		philo_sleep(philo);
		if (philo_is_sim_over(philo))
			break;
		philo_think(philo);
	}
	return (NULL);
}
