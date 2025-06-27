/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:44:13 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/27 12:04:25 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philo_usleep_simple(size_t us)
{
	size_t	start;

	start = philo_get_time();
	while ((philo_get_time() - start) < us)
		usleep(100);
	return (0);
}

/**
 * @brief Custom usleep function that sleeps for 'total_ms'
 *        but checks the simulation's dead_flag periodically.
 * @param philo Pointer to the philosopher's structure.
 * @param total_microseconds The total time to sleep in microseconds.
 * @return Returns 0 if sleep completed, 1 if interrupted by simulation end.
 * 
 * last if to check if the remaining time is small
 * waiting in the same loop iteration
 * 
 * Note: usleep works with microseconds us
 */
/*
int	philo_usleep(t_philo *philo, size_t total_ms)
{
	size_t	start_time_ms;
	size_t	elapsed_ms;

	start_time_ms = philo_get_time();
	while (1)
	{
		if (philo_is_sim_over(philo))
			return (1);
		elapsed_ms = philo_get_time() - start_time_ms;
		if (elapsed_ms >= total_ms)
			break ;
		if (total_ms - elapsed_ms < (USLEEP_CHECK_INTERVAL))
			usleep((total_ms - elapsed_ms) * 1000);
		else
			usleep(USLEEP_CHECK_INTERVAL * 1000);
	}
	return (0);
}
*/

int philo_usleep(t_philo *philo, size_t total_ms)
{
	size_t start_time_ms;
	
	start_time_ms = philo_get_time();
	while (philo_get_time() - start_time_ms < total_ms)
	{
		if (philo_is_sim_over(philo))
			return (1);
		// Sleep for a very short duration. 500 microseconds is a good balance
		// between responsiveness and not burning too much CPU.
		usleep(500);
	}
	return (0);
}

size_t	philo_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
