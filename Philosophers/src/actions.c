/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:43:40 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/01 00:20:47 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Performs the eating action: logs, updates state, delays, releases forks.
 * @param philo Pointer to the philosopher's structure.
 */
void	philo_eat(t_philo *philo)
{
	if (philo->philo_is_sim_over == 1)
	{
		philo_release_forks(philo);
		return ();
	}
	philo_log_state(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = philo_get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	release_forks(philo);
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
	log_state(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
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
	log_state(philo, "is thinking");
	//ft_usleep(1);
}
