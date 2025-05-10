/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:44:13 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/10 17:35:02 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Improved version of sleep function
 * @param time_ms (time in miliseconds)
 * 
 * usleep param: 500 ms OR ms / 10;
 */
int	philo_usleep(size_t time_ms)
{
	size_t	start;

	start = philo_get_time();
	while ((philo_get_time() - start) < time_ms)
		usleep(500);
	return (0);
}

size_t	philo_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
