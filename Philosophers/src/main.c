/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:46:03 by goteixei          #+#    #+#             */
/*   Updated: 2025/03/07 20:48:29 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (!(argc == 5 || argc == 6))
		return (write(2, "ERROR: Wrong argument count\n", 22), 1);
	if (philo_check_valid_args(argv) == 1)
		return (1);
	philo_init_program(&program, philos);
	philo_init_forks(forks, ft_atoi(argv[1]));
	philo_init_philos(philos, &program, forks, argv);
	philo_thread_create(&program, forks);
	philo_destory_all(NULL, &program, forks);
}
