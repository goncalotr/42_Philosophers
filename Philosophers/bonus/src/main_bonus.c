/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:46:03 by goteixei          #+#    #+#             */
/*   Updated: 2025/07/04 14:44:07 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../inc/philo_bonus.h"

/**
 * @brief Launches all philosopher processes.
 * @param program Pointer to the main program structure.
 * @return 0 on success, 1 on fork failure.
 * 
 * pid == 0 is the child process
 */
static int	philo_launch_philos(t_program *program)
{
	int		i;
	size_t	start_time;

	start_time = philo_get_time();
	i = 0;
	while (i < program->num_of_philos)
	{
		program->philos[i].start_time = start_time;
		program->philos[i].pid = fork();
		if (program->philos[i].pid < 0)
			return (philo_error("fork() failed"));
		if (program->philos[i].pid == 0)
		{
			philosopher_routine(&program->philos[i]);
			exit(0);
		}
		i++;
	}
	return (0);
}

/**
 * @brief A thread routine for the main process to wait for all meal signals.
 *        If the meal requirement is met, it posts to the dead_sem to
 *        stop the simulation.
 * @param arg A void pointer to the program struct.
 * @return NULL.
 * 
 * Wait for a signal from each philosopher that they have eaten enough
 * Once all have eaten, post to the dead semaphore to signal completion
 * We reuse the dead_sem to signal the end, regardless of the cause.
 */
void	*philo_waiter_routine(void *arg)
{
	t_program	*program;
	int			i;

	program = (t_program *)arg;
	i = 0;
	while (i < program->num_of_philos)
	{
		sem_wait(program->meals_sem);
		i++;
	}
	sem_post(program->dead_sem);
	return (NULL);
}

/**
 * @brief Main entry point for the bonus part.
 *        Initializes, launches, waits for completion, and cleans up.
 * 
 * 1 Initialize program data and semaphores
 * 2 If the meal limit is set, start the waiter thread
 * 3 Launch all philosopher child processes
 * 4 The main process now waits for an end signal.
 *    waits for dying philo or waiter end
 * 5 After end condition is met, clean up everything
 */
int	main(int argc, char **argv)
{
	t_program	program;
	pthread_t	waiter_thread;

	if (philo_init_program(&program, argc, argv) != 0)
		return (1);
	if (program.philos[0].num_times_to_eat > 0)
	{
		if (pthread_create(&waiter_thread, NULL, &philo_waiter_routine, &program))
		{
			philo_cleanup(&program);
			return (philo_error("Failed to create waiter thread"));
		}
	}
	if (philo_launch_philos(&program) != 0)
	{
		philo_cleanup(&program);
		return (1);
	}
	sem_wait(program.dead_sem);
	philo_cleanup(&program);
	if (program.philos[0].num_times_to_eat > 0)
		pthread_join(waiter_thread, NULL);
	return (0);
}
