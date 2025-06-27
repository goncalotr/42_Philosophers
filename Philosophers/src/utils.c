/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:17:37 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/27 14:49:53 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philo_error_msg(const char *str)
{
	write(2, "Error: ", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (1);
}

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
			return (philo_error_msg("Arguments must be valid."));
		if (temp_val <= 0 && i == 1)
			return (philo_error_msg("Number of philosophers must be > 0."));
		if (temp_val > INT_MAX)
			return (philo_error_msg("Argument value too large."));
		if (i == 1 && (temp_val > PHILO_MAX))
			return (philo_error_msg("Number of philosophers above PHILO_MAX."));
		if (i >= 2 && temp_val < 0)
			return (philo_error_msg("Time arguments/meals can't be negative"));
		i++;
	}
	return (0);
}
