/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:17:37 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/10 17:38:03 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
