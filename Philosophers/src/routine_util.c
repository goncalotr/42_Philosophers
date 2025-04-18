/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:10:31 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/18 19:15:53 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philo_simulation_over(t_philo *philo)
{
	int	result;
	
	pthread_mutex_lock(philo->dead_lock);
	result = *(philo->dead);
	pthread_mutex_unlock(philo->dead_lock);
	return (result);
}
