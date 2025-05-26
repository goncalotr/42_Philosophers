/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:29:17 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/27 00:50:59 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
 * @brief Checks if the command line arguments are valid numbers and counts.
 * @return 0 on success, 1 on error.
 */
int	philo_check_valid_args(int argc, char **argv)
{
	long	temp_val;
	int		i;

	if (argc < 5 || argc > 6)
		return (philo_error_msg("Wrong number of arguments."\
"Usage: ./philo num_philo time_die time_eat time_sleep [num_meals]"));
	i = 1;
	while (i < argc)
	{
		temp_val = ft_atol(argv[i]);
		if (temp_val == -1)
			return (philo_error_msg("Arguments must be positive integers."));
		if (temp_val == 0 && i == 1)
			return (philo_error_msg("Number of philosophers must be > 0."));
		if (temp_val > INT_MAX)
			return (philo_error_msg("Argument value too large."));
		if (i == 1 && temp_val > PHILO_MAX)
			return \
(philo_error_msg("Number of philosophers exceeds PHILO_MAX."));
		i++;
	}
	return (0);
}

/*
 * @brief Initializes the main program structure (mutexes, flags, args).
 * @return 0 on success, 1 on mutex init error.
 * 
 * num_times_to_eat = -1 -> default: no meal limit
 */
int	philo_init_program(t_program *program, t_philo *philos,\
		int argc, char **argv)
{
	program->philos = philos;
	program->argv = argv;
	program->dead_flag = 0;
	program->num_of_philos = ft_atol(argv[1]);
	program->num_times_to_eat = -1;
	if (argc == 6)
	{
		program->num_times_to_eat = ft_atol(argv[5]);
		if (program->num_times_to_eat == 0)
			program->dead_flag = 1;
	}
	if (pthread_mutex_init(&program->dead_lock, NULL) != 0)
		return (philo_error_msg("Mutex init failed (dead_lock)"));
	if (pthread_mutex_init(&program->meal_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&program->dead_lock);
		return (philo_error_msg("Mutex init failed (meal_lock)"));
	}
	if (pthread_mutex_init(&program->write_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&program->dead_lock);
		pthread_mutex_destroy(&program->meal_lock);
		return (philo_error_msg("Mutex init failed (write_lock)"));
	}
	return (0);
}

/**
 * @brief Initializes the mutexes for the forks.
 * @return 0 on success, 1 on error (destroys already created forks).
 */
int	philo_init_forks(pthread_mutex_t *forks, int num_philosophers)
{
	int	i;

	i = 0;
	while (i < num_philosophers)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&forks[i]);
			return (philo_error_msg("Mutex init failed (forks)"));
		}
		i++;
	}
	return (0);
}

/**
 * left_fork => fork_a
 * right_fork -> fork_b
 */
static void	philo_init_philos_aux(t_program *program,\
		pthread_mutex_t *forks, int i, size_t start_time)
{
	program->philos[i].id = i + 1;
	program->philos[i].eating = 0;
	program->philos[i].meals_eaten = 0;
	program->philos[i].num_of_philos = program->num_of_philos;
	program->philos[i].time_to_die = (size_t)ft_atol(program->argv[2]);
	program->philos[i].time_to_eat = (size_t)ft_atol(program->argv[3]);
	program->philos[i].time_to_sleep = (size_t)ft_atol(program->argv[4]);
	program->philos[i].num_times_to_eat = program->num_times_to_eat;
	program->philos[i].start_time = start_time;
	program->philos[i].last_meal_time = start_time;
	program->philos[i].program = program;
	program->philos[i].write_lock = &program->write_lock;
	program->philos[i].dead_lock = &program->dead_lock;
	program->philos[i].meal_lock = &program->meal_lock;
	program->philos[i].dead_flag = &program->dead_flag;
	program->philos[i].fork_a = &forks[i];
	program->philos[i].fork_b = &forks[(i + 1) \
% program->num_of_philos];
}

/**
 * @brief Initializes each philosopher's state.
 * Assumes program and forks are already successfully initialized.
 * @return Always 0 (success assumed if previous steps passed).
 * 
 * assign forks
 * left philo ID
 * right next philo ID
 */
int	philo_init_philos(t_program *program, pthread_mutex_t *forks)
{
	int		i;
	size_t	start_time;

	start_time = philo_get_time();
	i = 0;
	while (i < program->num_of_philos)
	{
		philo_init_philos_aux(program, forks, i, start_time);
		if (program->philos[i].id % 2 == 0)
		{
			program->philos[i].fork_a = \
&forks[(i + 1) % program->num_of_philos];
			program->philos[i].fork_b = &forks[i];
		}
		i++;
	}
	return (0);
}
