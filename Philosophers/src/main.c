/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:46:03 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/23 15:52:56 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Main entry point for the Philosophers simulation.
 * 
 * 1 Validate input arguments
 * 2 Init program
 * 3 Init fork mutexes
 * 4 Init individual philosopher states
 * 5 Create and run threads
 * 6 Cleanup
 */
int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (philo_check_valid_args(argc, argv) == 1)
		return (1);
	if (philo_init_program(&program, philos, argc, argv) != 0)
		return (1);
	if (philo_init_forks(forks, program.num_of_philos) != 0)
	{
		philo_destroy_all(NULL, &program, NULL);
		return (1);
	}
	if (philo_init_philos(&program, forks) != 0)
	{
		philo_destroy_all("Philosopher initialization failed", &program, forks);
		return (1);
	}
	if (philo_thread_create(&program, forks) != 0)
	{
		philo_destroy_all("Thread creation/joining failed.", &program, forks);
		return (1);
	}
	philo_destroy_all(NULL, &program, forks);
	return (0);
}
