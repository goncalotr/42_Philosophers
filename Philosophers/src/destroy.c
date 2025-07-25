/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:09:50 by goteixei          #+#    #+#             */
/*   Updated: 2025/07/05 11:53:06 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * Helper function to destroy fork mutexes.
 * Destroy mutexes one by one
 * 
 * don't free forks because
 * the forks array was allocated on the stack in main
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
}

static void	philo_destroy_program_mutexes(t_program *program)
{
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->write_lock);
}

static void	philo_destroy_philos(t_program *program)
{
	int	i;

	if (!program->philos)
		return ;
	i = 0;
	while (i < program->num_of_philos)
	{
		pthread_mutex_destroy(&program->philos[i].lock);
		i++;
	}
	free(program->philos);
	program->philos = NULL;
}

/**
 * @brief Destroys all initialized mutexes and frees allocated memory.
 *        Can optionally print an error message before cleanup.
 * @param msg An optional error message to print before cleaning up.
 * If NULL, no message is printed (normal cleanup).
 * @param program Pointer to the main program structure.
 * @param forks Pointer to the array of fork mutexes
 * (might be NULL if alloc failed).
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
		philo_error_msg(msg);
	if (program)
	{
		if (forks && program->num_of_philos > 0)
			philo_destroy_fork_mutexes(program, forks);
		philo_destroy_program_mutexes(program);
		philo_destroy_philos(program);
	}
	if (forks)
	{
		free(forks);
		forks = NULL;
	}
}
