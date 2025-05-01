/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:34:45 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/01 01:44:23 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * eat, sleep, think, check death...
 * 
*/
/*
void	*philosopher_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->write_lock);
	printf("Philo %d starting routine.\n", philo->id);
	pthread_mutex_unlock(philo->write_lock);
	while (1)
	{
		pthread_mutex_lock(philo->dead_lock);
		if (*(philo->dead_flag) == 1)
		{
			pthread_mutex_unlock(philo->dead_lock);
			break;
		}
		pthread_mutex_unlock(philo->dead_lock);
		philo_usleep(10);
	}
	pthread_mutex_lock(philo->write_lock);
	printf("Philo %d finishing routine.\n", philo->id);
	pthread_mutex_unlock(philo->write_lock);
	return (NULL);
}
*/
/*
void	*monitor_routine(void *arg)
{

}
*/

/**
 * @brief Creates and launches philosopher threads and the monitor thread.
 *        Waits (joins) for all threads to complete.
 * @param program Pointer to the main program structure.
 * @param forks Pointer to the array of fork mutexes (may not be needed directly).
 * @return 0 on success, 1 on failure (e.g., thread creation error).
 * 
 * 1 Create threads
 * 2 Minitor threads
 * 3 Join threads (wait for completion)
 */
/*
int	philo_thread_create(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	monitor_thread;
	int			i;
	(void)forks;

	i = 0;
	while (i < program->num_of_philos)
	{
		// Pass address of the specific philosopher struct as the argument
		if (pthread_create(&program->philos[i].thread, NULL, philosopher_routine,\
			&program->philos[i]) != 0)
		{
			return (philo_error_msg("Failed to create philosopher thread"));
			// TODO: Implement more robust cleanup if create fails mid-way
		}
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_routine, program) != 0)
	{
		return (philo_error_msg("Failed to create monitor thread"));
		// TODO: Implement cleanup of philosopher threads if monitor create fails
	}
	i = 0;
	while (i < program->num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
		{
			philo_error_msg("Failed to join philosopher thread");
		}
		i++;
	}
	if (pthread_join(monitor_thread, NULL) != 0)
	{
		philo_error_msg("Failed to join monitor thread");
	}
	return (0);
}
*/
