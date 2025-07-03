/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:48:08 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/27 14:57:56 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	philo_check_death_only(t_program *program)
{
	int	i;

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

static int	philo_check_death_and_meals(t_program *program, int *all_ate_flag)
{
	int	i;

	i = 0;
	*all_ate_flag = 1;
	while (i < program->num_of_philos)
	{
		pthread_mutex_lock(&program->philos[i].lock);
		if (philo_check_death(&program->philos[i]))
		{
			pthread_mutex_unlock(&program->philos[i].lock);
			return (philo_handle_death(program, i));
		}
		if (program->philos[i].meals_eaten < (size_t)program->num_times_to_eat)
			*all_ate_flag = 0;
		pthread_mutex_unlock(&program->philos[i].lock);
		i++;
	}
	return (philo_check_stop_conditions_aux(program, all_ate_flag));
}

/**
 * @brief Checks death and meal completion for all philosophers for one cycle.
 *        This function now acts as a dispatcher to the correct helper.
 */
static int	philo_check_stop_conditions(t_program *program, int *all_ate_flag)
{
	if (program->num_times_to_eat == -1)
	{
		*all_ate_flag = 0;
		return (philo_check_death_only(program));
	}
	else
	{
		return (philo_check_death_and_meals(program, all_ate_flag));
	}
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
