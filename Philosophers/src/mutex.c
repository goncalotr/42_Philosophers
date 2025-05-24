/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:40:18 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/24 13:49:25 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_setInt(pthread_mutex_t *mutex, int *target, int value)
{
	pthread_mutex_lock(mutex);
	*target = value;
	pthread_mutex_unlock(mutex);
	return ;
}

int	philo_getInt(pthread_mutex_t *mutex, int *value)
{
	int temp;

	pthread_mutex_lock(mutex);
	temp = *value;
	pthread_mutex_unlock(mutex);
	return (temp);
}
