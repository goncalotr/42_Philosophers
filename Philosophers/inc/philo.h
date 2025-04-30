/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:35:27 by goteixei          #+#    #+#             */
/*   Updated: 2025/05/01 00:06:26 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/**************************************************************************
 * SECTION: Libraries
 **************************************************************************/
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# include <pthread.h>
# include <sys/time.h>

# include <string.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>

/**************************************************************************
 * SECTION: Macros
 **************************************************************************/

// Colors
# define RESET		"\033[0m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define WHITE		"\033[37m"

# define PHILO_MAX 200

/**************************************************************************
 * SECTION: Structs
 **************************************************************************/

struct s_program;

// philo struct
// args; individual state; other
// 1 on true
// 0 off false
typedef struct s_philo
{
	size_t				num_of_philos;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	long				num_times_to_eat;
	pthread_t			thread;
	int					id;
	int					eating;
	size_t				meals_eaten;
	size_t				start_time;
	size_t				last_meal_time;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*meal_lock;
	int					*dead_flag;
	struct s_program	*program;
	int					dead;
}	t_philo;

typedef struct s_program
{
	int					dead_flag;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		write_lock;
	int					num_of_philos;
	long				num_times_to_eat;
	char				**argv;
	t_philo				*philos;
}	t_program;

/**************************************************************************
 * SECTION: Functions
 **************************************************************************/

// --- utils.c ---
int			ft_strlen(char *str);
int			ft_atol(char *str);

void		philo_destroy_all(char *str, t_program *program, pthread_mutex_t *forks);

int	philo_error_msg(char *str);
//int phi_error(char *str, t_data *data);

int			philo_usleep(size_t milliseconds);
size_t		philo_get_time(void);

// --- init.c ---
int			philo_check_valid_args(int argc, char **argv);
int			philo_init_program(t_program *program, t_philo *philos, int argc, char **argv);
int			philo_init_forks(pthread_mutex_t *forks, int num_philosophers);
int			philo_init_philos(t_program *program, pthread_mutex_t *forks);

// --- threads.c ---
int			philo_thread_create(t_program *program, pthread_mutex_t *forks);

// main
//int	main(int argc, char **argv);

#endif