/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:46:03 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/27 14:41:14 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	philo_alloc_philos(int num_philos, t_philo **philos_ptr)
{
	*philos_ptr = malloc(sizeof(t_philo) * num_philos);
	if (!(*philos_ptr))
	{
		philo_error_msg("Error: Failed to allocate memory for philosophers.");
		return (1);
	}
	return (0);
}

static int	philo_alloc_forks(int num_philos, t_philo **philos_ptr, \
pthread_mutex_t **forks_ptr)
{
	*forks_ptr = malloc(sizeof(pthread_mutex_t) * num_philos);
	if (!(*forks_ptr))
	{
		philo_error_msg("Failed to allocate memory for forks.");
		free(*philos_ptr);
		*philos_ptr = NULL;
		return (1);
	}
	return (0);
}

static int	philo_init_allocations(int num_philos, t_philo **philos_ptr, \
pthread_mutex_t **forks_ptr)
{
	if (philo_alloc_philos(num_philos, philos_ptr))
		return (1);
	if (philo_alloc_forks(num_philos, philos_ptr, forks_ptr))
		return (1);
	return (0);
}

static int	philo_init_main_aux(t_program *program, \
pthread_mutex_t **forks)
{
	if (philo_init_forks(*forks, program->num_of_philos) != 0)
	{
		philo_destroy_all(NULL, program, NULL);
		free(*forks);
		return (1);
	}
	if (philo_init_philos(program, *forks) != 0)
		return (philo_destroy_all("Error: \
Philosopher init failed", program, *forks), 1);
	return (0);
}

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
	t_philo			*philos;
	pthread_mutex_t	*forks;

	philos = NULL;
	forks = NULL;
	if (philo_check_valid_args(argc, argv) == 1)
		return (1);
	program.num_of_philos = ft_atol(argv[1]);
	if (program.num_of_philos == 0)
		return (philo_error_msg("Error: \
Number of philosophers cannot be zero."), 1);
	if (philo_init_allocations(program.num_of_philos, &philos, &forks))
		return (1);
	if (philo_init_program(&program, philos, argc, argv) != 0)
		return (free(philos), free(forks), 1);
	if (philo_init_main_aux(&program, &forks) != 0)
		return (1);
	if (philo_thread_create(&program, forks) != 0)
		return (1);
	philo_destroy_all(NULL, &program, forks);
	return (0);
}
