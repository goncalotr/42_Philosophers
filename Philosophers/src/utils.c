/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:17:37 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/02 14:05:17 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Improved version of sleep function
 * @param time_ms (time in miliseconds)
 * 
 * usleep param: 500 ms OR ms / 10;
 */
int	philo_usleep(size_t time_ms)
{
	size_t	start;

	start = philo_get_time();
	while ((philo_get_time() - start) < time_ms)
		usleep(500);
	return (0);
}

size_t	philo_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/*
 * @brief Prints status messages, protected by write_lock.
 * @param philo Philosopher performing the action.
 * @param status_msg The message (e.g., "is eating").
 * @param unlock_write If 1, unlocks write_lock after printing (for death msg).
 */
void	philo_print_status(t_philo *philo, char *status_msg, int unlock_write)
{
	size_t	time_ms;

	pthread_mutex_lock(&philo->program->write_lock); 
	pthread_mutex_lock(&philo->program->dead_lock);
	if (!philo->program->dead_flag)
	{
		time_ms = philo_get_time() - philo->start_time;
		printf("%zu %d %s\n", time_ms, philo->id, status_msg);
	}
	pthread_mutex_unlock(&philo->program->dead_lock);
	if (unlock_write)
		pthread_mutex_unlock(&philo->program->write_lock);
	else
		pthread_mutex_unlock(&philo->program->write_lock);
}

int	philo_error_msg(char *str)
{
	write(2, "Error: ", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (1);
}
