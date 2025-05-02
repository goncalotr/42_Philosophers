/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:48:08 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/02 12:42:15 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * Checks if a single philosopher has died.
 * Returns 1 if died, 0 otherwise. MUST be called with meal_lock held.
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
	pthread_mutex_lock(&program->dead_lock);
	if (!program->dead_flag)
	{
		program->dead_flag = 1;
		pthread_mutex_unlock(&program->dead_lock);
		philo_log_state(&program->philos[philo_index], "died");
	}
	else
	{
		pthread_mutex_unlock(&program->dead_lock);
	}
	return (1);
}

/**
 * Checks if all philosophers have eaten enough times (if required).
 * Returns 1 if all have eaten enough, 0 otherwise. Assumes meal_lock held.
 * 
 * Assumes meal_lock is ALREADY HELD by caller
 * And program->num_times_to_eat has already been checked to be > -1
 */
static int	check_all_ate(t_program *program)
{
	int		i;
	int		all_finished_eating;

	i = 0;
	all_finished_eating = 1;
	while (i < program->num_of_philos)
	{
		if (program->philos[i].meals_eaten < (size_t)program->num_times_to_eat)
		{
			all_finished_eating = 0;
			break ;
		}
		i++;
	}
	return (all_finished_eating);
}

Okay, you're right, the previous philo_monitor_sim was still likely over 25 lines, even with helpers. Let's break it down further to strictly adhere to the Norminette line limit.

We'll extract the main loop's body into another helper function.

      
#include "philo.h" // Or "../inc/philo.h"

// --- Need prototypes from other files ---
size_t	get_time(void);
int		ft_usleep(size_t milliseconds);
void	log_state(t_philo *philo, const char *state_msg);

/* --- Static Helper Function Prototypes for Monitor --- */
static int	check_philo_death(t_philo *philo);
static int	handle_death(t_program *program, int philo_index);
static int	check_all_ate(t_program *program);
static int	check_stop_conditions(t_program *program, int *all_ate_flag);

/* --- Helper Implementations (Keep these from previous example) --- */

/* Checks if a single philosopher has died. Assumes meal_lock held. */
static int	check_philo_death(t_philo *philo)
{
	// Assumes meal_lock is ALREADY HELD by caller
	if ((get_time() - philo->last_meal_time) >= philo->time_to_die)
	{
		return (1); // Died
	}
	return (0); // Still alive
}

/* Sets dead flag, logs death. Returns 1 to signal stop. */
static int	handle_death(t_program *program, int philo_index)
{
	pthread_mutex_lock(&program->dead_lock);
	if (!program->dead_flag) // Check flag again inside lock
	{
		program->dead_flag = 1;
		// Unlock dead_lock BEFORE calling log_state
		pthread_mutex_unlock(&program->dead_lock);
		log_state(&program->philos[philo_index], "died");
	}
	else
		pthread_mutex_unlock(&program->dead_lock);
	return (1); // Signal to stop monitoring
}

/* Checks if all philosophers ate enough. Assumes meal_lock held. */
static int	check_all_ate(t_program *program)
{
	int		i;
	int		all_finished_eating;

	// Assumes meal_lock is ALREADY HELD by caller
	// Assumes program->num_times_to_eat != -1 check done by caller
	i = 0;
	all_finished_eating = 1;
	while (i < program->num_of_philos)
	{
		if (program->philos[i].meals_eaten < (size_t)program->num_times_to_eat)
		{
			all_finished_eating = 0;
			break ;
		}
		i++;
	}
	return (all_finished_eating);
}

/**
 * @brief Checks death and meal completion for all philosophers for one cycle.
 *        Manages mutex locking for checks.
 * @param program Pointer to the main program structure.
 * @param all_ate_flag Pointer to flag indicating if meal goal met this cycle.
 * @return int Returns 1 if the simulation should stop, 0 otherwise.
 */
static int	check_stop_conditions(t_program *program, int *all_ate_flag)
{
	int	i;

	i = 0;
	*all_ate_flag = (program->num_times_to_eat != -1);
	while (i < program->num_of_philos)
	{
		pthread_mutex_lock(&program->meal_lock);
		if (check_philo_death(&program->philos[i]))
		{
			pthread_mutex_unlock(&program->meal_lock);
			return (handle_death(program, i));
		}
		if (program->num_times_to_eat != -1 && \
			program->philos[i].meals_eaten < (size_t)program->num_times_to_eat)
		{
			*all_ate_flag = 0;
		}
		pthread_mutex_unlock(&program->meal_lock);
		i++;
	}
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
 * @brief Monitors the simulation state in a loop using helper functions.
 *        Sets the program->dead_flag when the simulation should end.
 *        Runs in the main thread. Adheres to Norminette 25-line limit.
 * @param program Pointer to the main program structure.

 * Check meals only if death didn't occur and meal count is active
 * All Ate Condition Met (after unlock)
 * dead check to prevent race
 */
void philo_monitor_sim(t_program *program)
{
	int	stop_monitoring;
	int	all_ate_status;

	stop_monitoring = 0;
	while (!stop_monitoring)
	{
		stop_monitoring = philo_check_stop_conditions(program, &all_ate_status);
		if (!stop_monitoring)
			ft_usleep(1); 
	}
}
