/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:17:37 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/02 12:43:07 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
int	ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_atol(char *str)
{
	long int	number;
	int					sign;
	int					i;

	number = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (number > (LONG_MAX - (str[i] - '0')) / 10)
			return (-1);
		number = number * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (sign * number);
}


*/
/*
 * @brief Destroys mutexes. Can be called on error or successful exit.
 * @param err_msg If not NULL, prints this error message first.
 * @param program Pointer to the program struct.
 * @parint	philo_usleep(size_t time_ms)

	int	i;

	i = 0;
	if (str)
		philo_error_msg(str);
	if (program)
	{
		pthread_mutex_destroy(&program->write_lock);
		pthread_mutex_destroy(&program->meal_lock);
		pthread_mutex_destroy(&program->dead_lock);
	}
	if (forks && program && program->num_of_philos > 0)
	{
		i = 0;
		while (i < program->num_of_philos)
		{
			pthread_mutex_destroy(&forks[i]);
			i++;
		}
	}
}
*/
/*
int phi_error(char *str, t_data *data)
{
	printf("%s\n", str);
	if (data)
		ft_exit(data);
	return (1);
}
*/

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
