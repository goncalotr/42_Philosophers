/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:47:58 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/18 19:13:31 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_eat(t_philo *philo)
{
	printf("is eating");

}

void	philo_think(t_philo *philo)
{
	//todo
	printf("is thinking");
}

void	philo_sleep(t_philo *philo)
{
	//todo 
	printf("is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);

	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}


