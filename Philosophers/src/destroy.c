/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:09:50 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/02 13:32:27 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * Helper function to destroy fork mutexes.
 * Destroy mutexes one by one
 */
static void	philo_destroy_fork_mutexes(t_program *program, \
		pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (!forks)
		return ;
	while (i < program->num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

/**
 * Helper function to destroy shared mutexes within the program struct.
 */
static void	philo_destroy_shared_mutexes(t_program *program)
{
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->write_lock);
}

/**
 * @brief Destroys all initialized mutexes and frees allocated memory.
 *        Can optionally print an error message before cleanup.
 * @param msg An optional error message to print before cleaning up. If NULL,
 *            no message is printed (normal cleanup).
 * @param program Pointer to the main program structure.
 * @param forks Pointer to the array of fork mutexes (might be NULL if alloc failed).
 * 
 * Destroy resources in roughly the reverse order of creation
 * 1. Destroy shared mutexes
 * 2. Free philosophers array
 * 3. Destroy fork mutexes and free the forks array
 * 3.1. num_of_philos valid
 * 3.2. else if case where programm might be null be forks exist
 */
void	philo_destroy_all(const char *msg, t_program *program, \
							pthread_mutex_t *forks)
{
	if (msg)
	{
		printf("Error: %s\n", msg);
	}
	if (program)
	{
		philo_destroy_shared_mutexes(program);
		if (program->philos)
			free(program->philos);
	}
	if (program && program->num_of_philos > 0)
		philo_destroy_fork_mutexes(program, forks);
	else if (forks)
		free(forks);
}
