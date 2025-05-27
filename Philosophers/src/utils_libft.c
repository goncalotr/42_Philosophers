/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:05:21 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/27 11:33:19 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_strlen(const char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/**
 * whitespace characters
 * ' '  // space
 * '\t' // horizontal tab
 * '\n' // newline (line feed)
 * '\v' // vertical tab
 * '\f' // form feed
 * '\r' // carriage return
 */
static int	ft_atol_aux(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
	{
		i++;
	}
	return (i);
}

int	ft_atol(char *str)
{
	long int	number;
	int			sign;
	int			i;

	number = 0;
	sign = 1;
	i = 0;
	ft_atol_aux(str, i);
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
