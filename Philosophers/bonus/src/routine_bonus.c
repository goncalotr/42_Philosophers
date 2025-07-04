/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:24:54 by goteixei          #+#    #+#             */
/*   Updated: 2025/07/04 14:31:07 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../inc/philo_bonus.h"

/**
 * @brief The monitor routine, runs in a separate thread for each philosopher.
 *        Checks for death by starvation or for meal completion.
 * @param arg A void pointer to the philosopher's struct.
 * @return NULL. This routine terminates the process with exit().
 * 
 * check for death
 *  Lock printing
 *  sem_post(philo->dead_sem) Signal the main process that someone died
 * check if meal count is statisfied
 */
void	*philo_monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if ((get_time() - philo->last_meal_time) > (size_t)philo->time_to_die)
		{
			sem_wait(philo->write_sem);
			printf("%zu %d died\n", get_time() - philo->start_time, philo->id);
			sem_post(philo->dead_sem);
			exit(1);
		}
		if (philo->num_times_to_eat != -1 \
&& philo->meals_eaten >= philo->num_times_to_eat)
		{
			sem_post(philo->meals_sem);
			exit(0);
		}
		return (NULL);
	}
}

/**
 * @brief The main routine for each philosopher process.
 *        Launches a monitor thread and enters the eat-sleep-think cycle.
 * @param philo Pointer to the philosopher's data struct.
 * 
 * set the initial last meal time for the monitor
 * create monitor thread that will watch the current philo
 * stagger start for odd-numbered philos
 * main eat-sleep-think lifecycle loop
 */
void	philo_routine(t_philo *philo)
{
	philo->last_meal_time = philo->start_time;
	if (pthread_create(&philo->monitor_thread, NULL, &monitor_routine, philo))
	{
		philo_error("Failed to create monitor thread");
		exit(1);
	}
	if (philo->id % 2)
		usleep(1000);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	pthread_join(philo->monitor_thread, NULL);
	exit(0);
}
