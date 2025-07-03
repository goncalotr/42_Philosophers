/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:52:48 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/27 14:57:54 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * Checks if a single philosopher has died.
 * Returns 1 if died, 0 otherwise. MUST be called with meal_lock held.
 * 
 * >= -> >
 */
int	philo_check_death(t_philo *philo)
{
	if ((philo_get_time() - philo->last_meal_time) >= philo->time_to_die)
	{
		return (1);
	}
	return (0);
}

/**
 * Sets the dead flag and logs the death message.
 * Returns 1 to indicate simulation should stop.
 */
int	philo_handle_death(t_program *program, int philo_index)
{
	size_t	timestamp_ms;

	pthread_mutex_lock(&program->dead_lock);
	if (program->dead_flag)
	{
		pthread_mutex_unlock(&program->dead_lock);
		return (1);
	}
	program->dead_flag = 1;
	pthread_mutex_lock(&program->write_lock);
	timestamp_ms = philo_get_time() - program->philos[philo_index].start_time;
	printf("%zu %d died\n", timestamp_ms, program->philos[philo_index].id);
	pthread_mutex_unlock(&program->write_lock);
	pthread_mutex_unlock(&program->dead_lock);
	return (1);
}

/**
 * Checks if all philosophers have eaten enough times.
 * Returns 1 if all have eaten enough, 0 otherwise.
 */
int	philo_check_stop_conditions_aux(t_program *program, \
int *all_ate_flag)
{
	if (*all_ate_flag)
	{
		pthread_mutex_lock(&program->dead_lock);
		if (!program->dead_flag)
			program->dead_flag = 1;
		pthread_mutex_unlock(&program->dead_lock);
		return (1);
	}
	return (0);
}
