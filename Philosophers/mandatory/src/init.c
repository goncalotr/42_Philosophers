/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:29:17 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/27 14:51:59 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
 * @brief Initializes the main program structure (mutexes, flags, args).
 * @return 0 on success, 1 on mutex init error.
 * 
 * num_times_to_eat = -1 -> default: no meal limit
 */
int	philo_init_program(t_program *program, t_philo *philos, \
int argc, char **argv)
{
	program->philos = philos;
	program->argv = argv;
	program->dead_flag = 0;
	program->num_times_to_eat = -1;
	if (argc == 6)
	{
		program->num_times_to_eat = ft_atol(argv[5]);
		if (program->num_times_to_eat == 0)
			program->dead_flag = 1;
	}
	if (pthread_mutex_init(&program->dead_lock, NULL) != 0)
		return (philo_error_msg("Mutex init failed (dead_lock)"));
	if (pthread_mutex_init(&program->write_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&program->dead_lock);
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
 * 
 * removed from end of function:
 *	program->philos[i].fork_a = &forks[i];
 *	program->philos[i].fork_b = &forks[(i + 1) \
 *	% program->num_of_philos];
 *
 * pthread_mutex_t *forks,
 */
static void	philo_init_philos_aux(t_program *program, \
int i, size_t start_time)
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
	program->philos[i].dead_flag = &program->dead_flag;
}

static void	assign_forks(t_philo *philo, pthread_mutex_t *forks, int i)
{
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	int				num_philos;

	num_philos = philo->num_of_philos;
	left_f = &forks[i];
	right_f = &forks[(i + 1) % num_philos];
	if (left_f < right_f)
	{
		philo->fork_a = left_f;
		philo->fork_b = right_f;
	}
	else
	{
		philo->fork_a = right_f;
		philo->fork_b = left_f;
	}
}

/**
 * @brief Initializes each philosopher's state.
 * Assumes program and forks are already successfully initialized.
 * @return Always 0 (success assumed if previous steps passed).
 * 
 * Error handling: if this fails, we must destroy all previously
 * created personal locks before returning.
 */
int	philo_init_philos(t_program *program, pthread_mutex_t *forks)
{
	int				i;
	size_t			start_time;

	start_time = philo_get_time();
	i = 0;
	while (i < program->num_of_philos)
	{
		philo_init_philos_aux(program, i, start_time);
		if (pthread_mutex_init(&program->philos[i].lock, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&program->philos[i].lock);
			return (philo_error_msg("Failed to init philo lock"));
		}
		assign_forks(&program->philos[i], forks, i);
		i++;
	}
	return (0);
}
