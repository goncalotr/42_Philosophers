/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:10:31 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/02 14:10:44 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Safely checks if the simulation has ended.
 * @param philo Pointer to the philosopher's structure.
 * @return 1 if simulation is over (death flag set), 0 otherwise.
 * 
 * *(data->dead) ??
 */
int	philo_is_sim_over(t_philo *data)
{
	int	result;

	pthread_mutex_lock(data->dead_lock);
	result = *(data->dead_flag);
	pthread_mutex_unlock(data->dead_lock);
	return (result);
}

/**
 * Helper function to safely check the simulation status *without* double-locking
 * the dead_lock if log_state is called after setting the dead_flag but before
 * unlocking dead_lock (e.g., in handle_death). This check assumes write_lock
 * is already held by the caller (log_state).
 */
static int	philo_check_dead_flag_unsafe(t_philo *philo)
{
	int	flag;

	flag = *(philo->dead_flag);
	return (flag);
}

/**
 * @brief Logs the philosopher's state with a timestamp, protected by a mutex.
 *        Ensures messages are not printed after the simulation end flag is set.
 * @param philo Pointer to the philosopher's structure.
 * @param state_msg The message describing the state (e.g., "is eating").
 */
void	philo_log_state(t_philo *philo, const char *state_msg)
{
	size_t	timestamp_ms;

	pthread_mutex_lock(philo->write_lock);
	if (!philo_check_dead_flag_unsafe(philo))
	{
		timestamp_ms = philo_get_time() - philo->start_time;
		printf("%zu %d %s\n", timestamp_ms, philo->id, state_msg);
	}
	pthread_mutex_unlock(philo->write_lock);
}
