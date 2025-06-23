/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:38:57 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/23 18:38:53 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Releases (unlocks) both forks held by the philosopher.
 * @param philo Pointer to the philosopher's structure.
 */
void	philo_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_a);
	if (philo->num_of_philos > 1)
		pthread_mutex_unlock(philo->fork_b);
}

/**
 * @brief Attempts to acquire both left and right forks using an ordered
 *        locking strategy (odd/even ID) to prevent deadlock.
 *        Handles the single philosopher case.
 * @param philo Pointer to the philosopher's structure.
 * 
 * Even IDs take the right fork first
 * Odd IDs take the left fork first
 * 
 * Determine order based on fork address
 * (or index if forks are an array)
 * 
 * num philos = 1
 * 
 * philo_usleep(philo, philo->time_to_die * 2);
 * philo_usleep(philo, philo->time_to_die + 10);
 *
 * philo_take_forks_aux becomes trivial or can be removed
 * philo_take_forks_ordered directly uses philo->fork_a and philo->fork_b
 */
int	philo_take_forks_ordered(t_philo *philo)
{
	if (philo_is_sim_over(philo))
		return (1);
	pthread_mutex_lock(philo->fork_a);
	philo_log_state(philo, "has taken a fork");
	if (philo_is_sim_over(philo))
		return (pthread_mutex_unlock(philo->fork_a), 1);
	if (philo->num_of_philos == 1)
	{
		philo_usleep(philo, philo->time_to_die);
		pthread_mutex_unlock(philo->fork_a);
		return (1);
	}
	pthread_mutex_lock(philo->fork_b);
	if (philo_is_sim_over(philo))
	{
		pthread_mutex_unlock(philo->fork_b);
		pthread_mutex_unlock(philo->fork_a);
		return (1);
	}
	philo_log_state(philo, "has taken a fork");
	return (0);
}
