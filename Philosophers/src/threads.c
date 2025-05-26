/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:34:45 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/27 00:42:12 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * Helper function to join threads in case of creation failure.
 */
static void	philo_join_created_threads(t_program *program, int num_created)
{
	while (--num_created >= 0)
	{
		pthread_join(program->philos[num_created].thread, NULL);
	}
}

/**
 * Main thread creation loop.
 * 
 * return 0 - success
 * return 1 - failure
 */
static int	philo_create_threads_loop(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, \
philo_routine, &program->philos[i]) != 0)
		{
			pthread_mutex_lock(&program->dead_lock);
			program->dead_flag = 1;
			pthread_mutex_unlock(&program->dead_lock);
			printf("Error: Failed to create thread for philo %d\n", i + 1);
			philo_join_created_threads(program, i);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * Main thread joining loop.
 */
static int	philo_join_thread_loop(t_program *program)
{
	int	i;
	int	error_flag;

	i = 0;
	error_flag = 0;
	while (i < program->num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
		{
			printf("Warning: Failed to join thread for philo %d\n", i + 1);
			error_flag = 1;
		}
		i++;
	}
	return (error_flag);
}

/**
 * @brief Creates, runs, monitors, and joins philosopher threads.
 * @param program Pointer to the main program structure.
 * @param forks Not directly used if philo->left/right_fork are set correctly.
 * @return 0 on success, non-zero on failure.
 * 
 * Initialize last_meal time AFTER getting start_time
 * Error handled within create_threads_loop, just return failure
 * Monitoring
 * Joining
 * Return failure or success
 */
int	philo_thread_create(t_program *program, pthread_mutex_t *forks)
{
	(void)forks;
	if (philo_create_threads_loop(program) != 0)
	{
		philo_destroy_all("Error creating threads", program, forks);
		return (1);
	}
	philo_monitor_sim(program);
	if (philo_join_thread_loop(program) != 0)
	{
	}
	return (0);
}
