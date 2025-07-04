/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:20:34 by goteixei          #+#    #+#             */
/*   Updated: 2025/07/04 14:51:12 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../inc/philo_bonus.h"

/**
 * @brief The philosopher takes two forks from the central pool.
 *        This is done by waiting on the forks semaphore twice.
 * @param philo Pointer to the philosopher's data struct.
 */
void	philo_take_forks(t_philo *philo)
{
	sem_wait(philo->forks_sem);
	philo_log_state(philo, "has taken a fork");
	sem_wait(philo->forks_sem);
	philo_log_state(philo, "has taken a fork");
}

/**
 * @brief The philosopher releases two forks back to the central pool.
 *        This is done by posting to the forks semaphore twice.
 * @param philo Pointer to the philosopher's data struct.
 */
void	philo_release_forks(t_philo *philo)
{
	sem_post(philo->forks_sem);
	sem_post(philo->forks_sem);
}

/**
 * @brief The philosopher performs the eating action.
 *        Logs the state, updates last meal time, sleeps, and increments
 *        the meal count.
 * @param philo Pointer to the philosopher's data struct.
 */
void	philo_eat(t_philo *philo)
{
	philo_log_state(philo, "is eating");
	philo->last_meal_time = philo_get_time();
	usleep(philo->time_to_eat * 1000);
	philo->meals_eaten++;
}

/**
 * @brief The philosopher performs the sleeping action.
 * @param philo Pointer to the philosopher's data struct.
 */
void	philo_sleep(t_philo *philo)
{
	philo_log_state(philo, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
}

/**
 * @brief The philosopher performs the thinking action.
 * @param philo Pointer to the philosopher's data struct.
 */
void	philo_think(t_philo *philo)
{
	philo_log_state(philo, "is thinking");
}
