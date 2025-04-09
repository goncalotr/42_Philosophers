/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:46:03 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/09 10:38:55 by goteixei         ###   ########.fr       */
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

	if (!(argc == 5 || argc == 6))
		return (write(2, "ERROR: Wrong argument count\n", 22), 1);
	if (philo_check_valid_args(argv) == 1)
		return (1);
	if (philo_init_program(&program, philos) != 0);
		return (1);
	if (philo_init_forks(forks, ft_atoi(argv[1])) != 0)
	{
		philo_destroy_all(NULL, &program, NULL);
		return (1);
	}
	if (philo_init_philos(philos, &program) != 0)
	{
		philo_destroy_all("Philosopher initialization failed, &program, forks");
		return (1);
	}
	if (philo_thread_create(&program, forks) != 0)
	{
		philo_destroy_all("Thread creation/joining failed.", &program, forks);
		return (1);
	}
	philo_destory_all(NULL, &program, forks);
	return (0);
}
