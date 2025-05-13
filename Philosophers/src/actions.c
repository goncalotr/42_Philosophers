/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:43:40 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/13 17:59:12 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Performs the eating action: logs, updates state, delays, 
 * releases forks.
 * @param philo Pointer to the philosopher's structure.
 * 
 * 1. Check if simulation ended BEFORE starting the action
 * 2. Log the action
 * 3. Update critical state (protected by mutex)
 * 4. Perform the actual eating delay
 * 5. Release resources after eating is finished
 */
void	philo_eat(t_philo *philo)
{
	if (philo_is_sim_over(philo))
	{
		philo_release_forks(philo);
		return ;
	}
	//sleep
	philo_log_state(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal_time = philo_get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	philo_usleep(philo, philo->time_to_eat);
	philo_release_forks(philo);
}

/**
 * @brief Performs the sleeping action: logs state and delays.
 * @param philo Pointer to the philosopher's structure.
 * 
 * 1. Check if simulation ended
 * 2. Log the action
 * 3. Perform the required sleeping delay
 */
void	philo_sleep(t_philo *philo)
{
	if (philo_is_sim_over(philo))
	{
		return ;
	}
	philo_log_state(philo, "is sleeping");
 	//philo_usleep(philo, 500);
	philo_usleep(philo, philo->time_to_sleep);
}

/**
 * @brief Performs the thinking action: logs state.
 * @param philo Pointer to the philosopher's structure.
 * 
 * 1. Check if simulation ended
 * 2. Log the action
 * 3. Optional small delay
 *    usleep for small delay
 *    ft_usleep(1) or ft_usleep(100)
 */
void	philo_think(t_philo *philo)
{
	if (philo_is_sim_over(philo))
	{
		return ;
	}
	philo_log_state(philo, "is thinking");
 	//usleep(500);
}
