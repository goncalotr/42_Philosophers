/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:43:40 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/02 18:37:20 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Performs the eating action: logs, updates state, delays, releases forks.
 * @param philo Pointer to the philosopher's structure.
 */
void	philo_eat(t_philo *philo)
{
	if (philo_is_sim_over(philo))
	{
		philo_release_forks(philo);
		return ;
	}
	philo_log_state(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal_time = philo_get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo_usleep(philo->time_to_eat);
	philo_release_forks(philo);
}

/**
 * @brief Performs the sleeping action: logs state and delays.
 * @param philo Pointer to the philosopher's structure.
 */
void	philo_sleep(t_philo *philo)
{
	if (philo_is_sim_over(philo))
	{
		return ;
	} 
	philo_log_state(philo, "is sleeping");
	philo_usleep(philo->time_to_sleep);
}

/**
 * @brief Performs the thinking action: logs state.
 * @param philo Pointer to the philosopher's structure.
 * 
 * usleep for small delay
 */
void	philo_think(t_philo *philo)
{
	if (philo_is_sim_over(philo))
	{
		return ;
	}
	philo_log_state(philo, "is thinking");
	//ft_usleep(1);
}
