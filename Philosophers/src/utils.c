/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:17:37 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/09 09:03:55 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

int	ft_atoi(char *str)
{
	unsigned long long	number;
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
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	return (sign * number);
}

/*
 * @brief
 * @param
 */

void	phi_destory_all(char *str, t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->dead_lock);
	while (i < program->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int phi_error(char *str, t_data *data)
{
	printf("%s\n", str);
	if (data)
		ft_exit(data);
	return (1);
}

/**
 * @brief Improved version of sleep function
 * @param milliseconds
 * 
 * usleep param: 500 ms; ms / 10;
 */
int	phi_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(milliseconds / 10);
	return (0);
}

size_t	phi_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
