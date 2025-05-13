/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:38:57 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/13 18:48:57 by goteixei         ###   ########.fr       */
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
 * @brief Determines the order of forks to pick up for deadlock prevention
 *        and assigns them to the provided pointer-to-pointer arguments.
 * @param philo Pointer to the philosopher's structure.
 * @param first_fork_ptr Pointer to a pthread_mutex_t pointer, will be set
 *                       to the first fork to lock.
 * @param second_fork_ptr Pointer to a pthread_mutex_t pointer, will be set
 *                        to the second fork to lock.
 */
static void	philo_take_forks_aux(t_philo *philo, \
	pthread_mutex_t	**first_fork_ptr, pthread_mutex_t	**second_fork_ptr)
{
	/*
	if (philo->id % 2 == 0)
	{
		*first_fork_ptr = philo->right_fork;
		*second_fork_ptr = philo->left_fork;
	}
	else
	{
		*first_fork_ptr = philo->left_fork;
		*second_fork_ptr = philo->right_fork;
	}
	*/

	if (philo->fork_a < philo->fork_b) 
	{
		*first_fork_ptr = philo->fork_a;
		*second_fork_ptr = philo->fork_b;
	}
	else
	{
		*first_fork_ptr = philo->fork_b;
		*second_fork_ptr = philo->fork_a;
	}
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
 * philo_usleep(philo, philo->time_to_die * 2);
 * philo_usleep(philo, philo->time_to_die + 10);
 */
void	philo_take_forks_ordered(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	philo_take_forks_aux(philo, &first_fork, &second_fork);
	if (philo_is_sim_over(philo))
		return ;
	pthread_mutex_lock(first_fork);
	philo_log_state(philo, "has taken a fork");
	if (philo_is_sim_over(philo))
	{
		pthread_mutex_unlock(first_fork);
		return ;
	}
	if (philo->num_of_philos == 1)
	{
		philo_usleep(philo, philo->time_to_die + 10);
		pthread_mutex_unlock(first_fork);
		return ;
	}
	pthread_mutex_lock(second_fork);
	if (philo_is_sim_over(philo))
	{
		pthread_mutex_unlock(second_fork); 
		pthread_mutex_unlock(first_fork);
		return ;
	}
	philo_log_state(philo, "has taken a fork");
}
