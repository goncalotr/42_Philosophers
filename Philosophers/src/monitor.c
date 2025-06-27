/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:48:08 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/27 13:33:46 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * Checks if a single philosopher has died.
 * Returns 1 if died, 0 otherwise. MUST be called with meal_lock held.
 * 
 * >= -> >
 */
static int	philo_check_death(t_philo *philo)
{
	if ((philo_get_time() - philo->last_meal_time) >= philo->time_to_die)
	{
		return (1);
	}
	return (0);
}

/**
 * Sets the dead flag and logs the death message.
 * Returns 1 to indicate simulation should stop.
 */
static int	philo_handle_death(t_program *program, int philo_index)
{
	size_t	timestamp_ms;

	pthread_mutex_lock(&program->dead_lock);
	if (program->dead_flag)
	{
		pthread_mutex_unlock(&program->dead_lock);
		return (1);
	}
	program->dead_flag = 1;
	pthread_mutex_lock(&program->write_lock);
	timestamp_ms = philo_get_time() - program->philos[philo_index].start_time;
	printf("%zu %d died\n", timestamp_ms, program->philos[philo_index].id);
	pthread_mutex_unlock(&program->write_lock);
	pthread_mutex_unlock(&program->dead_lock);
	return (1);
}

/**
 * Checks if all philosophers have eaten enough times.
 * Returns 1 if all have eaten enough, 0 otherwise.
 */
static int	philo_check_stop_conditions_aux(t_program *program, \
int *all_ate_flag)
{
	if (*all_ate_flag)
	{
		pthread_mutex_lock(&program->dead_lock);
		if (!program->dead_flag)
			program->dead_flag = 1;
		pthread_mutex_unlock(&program->dead_lock);
		return (1);
	}
	return (0);
}

/**
 * @brief Checks death and meal completion for all philosophers for one cycle.
 *        Manages mutex locking for checks.
 * @param program Pointer to the main program structure.
 * @param all_ate_flag Pointer to flag indicating if meal goal met this cycle.
 * @return int Returns 1 if the simulation should stop, 0 otherwise.
 * 
 * assume that everyone has eaten enough - all ate = 1
 */
/*
static int	philo_check_stop_conditions(t_program *program, int *all_ate_flag)
{
	int	i;

	if (program->num_times_to_eat == -1)
	{
		*all_ate_flag = 0;
		return (0);
	}
	i = 0;
	*all_ate_flag = 1;
	while (i < program->num_of_philos)
	{
		//pthread_mutex_lock(&program->meal_lock);
		pthread_mutex_lock(&program->philos[i].lock);
		if (philo_check_death(&program->philos[i]))
		{
			//pthread_mutex_unlock(&program->meal_lock);
			pthread_mutex_unlock(&program->philos[i].lock);
			return (philo_handle_death(program, i));
		}
		if (program->num_times_to_eat != -1 && \
program->philos[i].meals_eaten < (size_t)program->num_times_to_eat)
			*all_ate_flag = 0;
		//pthread_mutex_unlock(&program->meal_lock);
		pthread_mutex_lock(&program->philos[i].lock);
		i++;
	}
	if (philo_check_stop_conditions_aux(program, all_ate_flag))
	{
		return (1);
	}
	return (0);
}
*/

static int philo_check_stop_conditions(t_program *program, int *all_ate_flag)
{
	int i;

	// This part is fine. If no meal limit, we don't need to check.
	if (program->num_times_to_eat == -1)
	{
		// We only check for death if there's no meal limit
		i = 0;
		while (i < program->num_of_philos)
		{
			pthread_mutex_lock(&program->philos[i].lock);
			if (philo_check_death(&program->philos[i]))
			{
				pthread_mutex_unlock(&program->philos[i].lock);
				return (philo_handle_death(program, i));
			}
			pthread_mutex_unlock(&program->philos[i].lock);
			i++;
		}
		return (0);
	}

	// This part handles the case WITH a meal limit.
	i = 0;
	*all_ate_flag = 1; // Assume everyone has eaten
	while (i < program->num_of_philos)
	{
		pthread_mutex_lock(&program->philos[i].lock); // LOCK
		if (philo_check_death(&program->philos[i]))
		{
			pthread_mutex_unlock(&program->philos[i].lock);
			return (philo_handle_death(program, i));
		}
		if (program->philos[i].meals_eaten < (size_t)program->num_times_to_eat)
			*all_ate_flag = 0; // The assumption was wrong
		
		pthread_mutex_unlock(&program->philos[i].lock); // UNLOCK (This was the bug)
		i++;
	}

	// If the flag is still 1, the simulation is over.
	if (philo_check_stop_conditions_aux(program, all_ate_flag))
	{
		return (1);
	}
	return (0);
}

/**
 * @brief Monitors the simulation state in a loop using helper functions.
 *        Sets the program->dead_flag when the simulation should end.
 *        Runs in the main thread. Adheres to Norminette 25-line limit.
 * @param program Pointer to the main program structure.

 * Check meals only if death didn't occur and meal count is active
 * All Ate Condition Met (after unlock)
 * dead check to prevent race
 * 
 * Small delay to prevent busy-waiting in the monitor loop.
 * 1 ms delay
 */
void	philo_monitor_sim(t_program *program)
{
	int	stop_monitoring;
	int	all_ate_status;

	stop_monitoring = 0;
	while (!stop_monitoring)
	{
		stop_monitoring = philo_check_stop_conditions(program, &all_ate_status);
		if (!stop_monitoring)
			usleep(1000);
	}
}
