/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:01:23 by goteixei          #+#    #+#             */
/*   Updated: 2025/07/04 14:49:02 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../inc/philo_bonus.h"

/**
 * @brief Initializes the semaphores for the simulation.
 *        Unlinks any existing semaphores before creating new ones.
 * @param program Pointer to the main program structure.
 * @return 0 on success, 1 on failure.
 */
int	philo_init_semaphores(t_program *program)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_MEALS);
	program->forks_sem = sem_open(SEM_FORKS, O_CREAT, 0644,
			program->num_of_philos);
	if (program->forks_sem == SEM_FAILED)
		return (philo_error("sem_open for forks failed"));
	program->write_sem = sem_open(SEM_WRITE, O_CREAT, 0644, 1);
	if (program->write_sem == SEM_FAILED)
		return (philo_error("sem_open for write failed"));
	program->dead_sem = sem_open(SEM_DEAD, O_CREAT, 0644, 0);
	if (program->dead_sem == SEM_FAILED)
		return (philo_error("sem_open for dead failed"));
	program->meals_sem = sem_open(SEM_MEALS, O_CREAT, 0644, 0);
	if (program->meals_sem == SEM_FAILED)
		return (philo_error("sem_open for meals failed"));
	return (0);
}

/**
 * @brief Initializes the data for each individual philosopher.
 * @param program Pointer to the main program structure.
 * 
 * -1: Initialize PID as invalid
 * Each philosopher gets pointers to the main semaphores
 */
static void	philo_init_philos(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		program->philos[i].id = i + 1;
		program->philos[i].pid = -1;
		program->philos[i].meals_eaten = 0;
		program->philos[i].num_of_philos = program->num_of_philos;
		program->philos[i].time_to_die = program->philos[0].time_to_die;
		program->philos[i].time_to_eat = program->philos[0].time_to_eat;
		program->philos[i].time_to_sleep = program->philos[0].time_to_sleep;
		program->philos[i].num_times_to_eat = \
program->philos[0].num_times_to_eat;
		program->philos[i].forks_sem = program->forks_sem;
		program->philos[i].write_sem = program->write_sem;
		program->philos[i].dead_sem = program->dead_sem;
		program->philos[i].meals_sem = program->meals_sem;
		i++;
	}
}

/**
 * @brief Parses command-line arguments and initializes the main program struct.
 * @param program Pointer to the main program structure.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return 0 on success, 1 on failure.
 * 
 * Store args in the first philosopher struct temporarily for distribution
 * -1: Default: no meal limit
 */
int	philo_init_program(t_program *program, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (philo_error("Usage: ./philo_bonus num_philos time_die \
time_eat time_sleep [num_meals]"));
	program->num_of_philos = ft_atol(argv[1]);
	if (program->num_of_philos <= 0 || program->num_of_philos > 200)
		return (philo_error("Number of philosophers must be between \
1 and 200"));
	program->philos[0].time_to_die = ft_atol(argv[2]);
	program->philos[0].time_to_eat = ft_atol(argv[3]);
	program->philos[0].time_to_sleep = ft_atol(argv[4]);
	if (program->philos[0].time_to_die < 0 || program->philos[0].time_to_eat < 0
		|| program->philos[0].time_to_sleep < 0)
		return (philo_error("Time arguments cannot be negative"));
	program->philos[0].num_times_to_eat = -1;
	if (argc == 6)
	{
		program->philos[0].num_times_to_eat = ft_atol(argv[5]);
		if (program->philos[0].num_times_to_eat <= 0)
			return (philo_error("Number of meals must be a positive number"));
	}
	philo_init_philos(program);
	return (philo_init_semaphores(program));
}
