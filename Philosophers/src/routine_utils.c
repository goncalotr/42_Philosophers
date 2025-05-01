/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:10:31 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/01 00:38:51 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Safely checks if the simulation has ended.
 * @param philo Pointer to the philosopher's structure.
 * @return 1 if simulation is over (death flag set), 0 otherwise.
 */
int	philo_is_sim_over(t_philo *data)
{
	int	result;

	pthread_mutex_lock(data->dead_lock);
	result = *(data->dead);
	pthread_mutex_unlock(data->dead_lock);
	return (result);
}
