/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:55:20 by goteixei          #+#    #+#             */
/*   Updated: 2025/07/04 14:02:09 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../inc/philo_bonus.h"

/**
 * @brief Prints an error message to stderr.
 * @param msg The error message to print.
 * @return Always returns 1, useful for `return (philo_error(...));`
 */
int	philo_error(const char *msg)
{
	printf("Error: %s\n", msg);
	return (1);
}

/**
 * @brief Converts a string to a long integer.
 * @param str The string to convert.
 * @return The converted long integer, or -1 on error (invalid format, overflow).
 */
int	ft_atol(const char *str)
{
	long int	number;
	int			i;

	number = 0;
	i = 0;
	if (!str)
		return (-1);
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		if (number > LONG_MAX)
			return (-1);
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return ((int)number);
}

/**
 * @brief Logs the state of a philosopher to standard output.
 *        Uses a semaphore to ensure that log messages are not interleaved.
 * @param philo Pointer to the philosopher's data struct.
 * @param state_msg The message describing the philosopher's current state.
 * 
 * sem_wait: Wait for the write semaphore to ensure exclusive access to stdout
 * sem_post: Release the write semaphore
 */
void	philo_log_state(t_philo *philo, const char *state_msg)
{
	size_t	timestamp_ms;

	sem_wait(philo->write_sem);
	timestamp_ms = get_time() - philo->start_time;
	printf("%zu %d %s\n", timestamp_ms, philo->id, state_msg);
	sem_post(philo->write_sem);
}

/**
 * @brief Cleans up resources: kills child processes and unlinks semaphores.
 * @param program Pointer to the main program structure.
 * 
 * 1 Kill any remaining child processes
 * 2 Close and unlink all named semaphores
 */
void	ms_cleanup(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		if (program->philos[i].pid > 0)
			kill(program->philos[i].pid, SIGKILL);
		i++;
	}
	if (program->forks_sem != SEM_FAILED)
		sem_close(program->forks_sem);
	if (program->write_sem != SEM_FAILED)
		sem_close(program->write_sem);
	if (program->dead_sem != SEM_FAILED)
		sem_close(program->dead_sem);
	if (program->meals_sem != SEM_FAILED)
		sem_close(program->meals_sem);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_MEALS);
}
