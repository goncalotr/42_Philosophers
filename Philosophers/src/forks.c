/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:38:57 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/02 18:42:47 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Releases (unlocks) both forks held by the philosopher.
 * @param philo Pointer to the philosopher's structure.
 */
void	philo_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	if (philo->num_of_philos > 1)
		pthread_mutex_unlock(philo->right_fork);
}

/**
 * @brief Attempts to acquire both left and right forks using an ordered
 *        locking strategy (odd/even ID) to prevent deadlock.
 *        Handles the single philosopher case.
 * @param philo Pointer to the philosopher's structure.
 */
void	philo_take_forks_ordered(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	else
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	pthread_mutex_lock(first_fork);
	if (philo_is_sim_over(philo))
	{
		pthread_mutex_unlock(first_fork);
		return ;
	}
	if (philo->num_of_philos == 1)
	{
		philo_usleep(philo->time_to_die * 2);
		pthread_mutex_unlock(first_fork);
		return ;
	}
	pthread_mutex_lock(second_fork);
	philo_log_state(philo, "has taken a fork");
}
