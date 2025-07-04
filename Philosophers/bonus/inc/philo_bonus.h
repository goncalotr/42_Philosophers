/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:35:27 by goteixei          #+#    #+#             */
/*   Updated: 2025/07/04 14:43:53 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/**************************************************************************
 * SECTION: Libraries
 **************************************************************************/
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# include <sys/time.h>

# include <string.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>

# include <pthread.h>	// monitor thread
# include <semaphore.h>	// main bonus library
# include <fcntl.h>		// O_CREAT, O_EXCL
# include <signal.h>	// kill()

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

# define PHILO_MAX 300
# define USLEEP_CHECK_INTERVAL 1 // in miliseconds, check every ms

// Semaphore names (must start with '/')
# define SEM_FORKS "/philo_forks_sem"
# define SEM_WRITE "/philo_write_sem"
# define SEM_DEAD  "/philo_dead_sem"
# define SEM_MEALS "/philo_meals_sem"

/**************************************************************************
 * SECTION: Structs
 **************************************************************************/

struct	s_program;

// philo struct
// args; individual state; other
// 1 on true
// 0 off false
// time in ms
typedef struct s_philo
{
	int				id;
	pid_t			pid;
	long			num_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			num_times_to_eat;

	long			meals_eaten;
	size_t			start_time;
	size_t			last_meal_time;

	sem_t			*forks_sem;
	sem_t			*write_sem;
	sem_t			*dead_sem;
	sem_t			*meals_sem;

	pthread_t		monitor_thread;
}	t_philo;

typedef struct s_program
{
	long			num_of_philos;
	t_philo			philos[300];

	sem_t			*forks_sem;
	sem_t			*write_sem;
	sem_t			*dead_sem;
	sem_t			*meals_sem;
}	t_program;

/**************************************************************************
 * SECTION: Functions
 **************************************************************************/

// --- main_bonus.c ---
int		main(int argc, char **argv);
void	*philo_waiter_routine(void *arg);

// --- init_bonus.c ---
int		philo_init_program(t_program *program, int argc, char **argv);

// --- routine_bonus.c ---
void	philosopher_routine(t_philo *philo);

// --- actions_bonus.c ---
void	philo_take_forks(t_philo *philo);
void	philo_release_forks(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

// --- time_bonus.c ---
size_t	philo_get_time(void);

// --- utils_bonus.c ---
int		philo_error(const char *msg);
int		ft_atol(const char *str);
void	philo_log_state(t_philo *philo, const char *state_msg);
void	philo_cleanup(t_program *program);

#endif