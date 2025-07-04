/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:59:48 by goteixei          #+#    #+#             */
/*   Updated: 2025/07/04 14:02:02 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../inc/philo_bonus.h"

/**
 * @brief Gets the current time in milliseconds since the Epoch.
 * @return The current time in milliseconds (size_t).
 */
size_t	philo_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		philo_error("gettimeofday() failed");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
