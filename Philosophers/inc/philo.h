/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:35:27 by goteixei          #+#    #+#             */
/*   Updated: 2025/03/31 13:22:24 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/**************************************************************************
 * SECTION: Libraries
 **************************************************************************/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// u_int64_t
# include <stdint.h>
// threads
# include <pthread.h>
// timeval gettimeofday
# include <sys/time.h>

/**************************************************************************
 * SECTION: Macros
 **************************************************************************/

# define PHILO_MAX 300

/**************************************************************************
 * SECTION: Structs
 **************************************************************************/

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				eating;
	size_t			start_time;
	size_t			last_meal;
	int				*dead;

	int				num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_times_must_eat;

	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
} t_philo;

/**************************************************************************
 * SECTION: Functions
 **************************************************************************/


#endif