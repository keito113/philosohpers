/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 10:06:05 by keitabe           #+#    #+#             */
/*   Updated: 2025/11/16 07:07:42 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_log(t_philo *philo, const char *msg)
{
	t_sim	*sim;
	long	ts;

	sim = philo->sim;
	pthread_mutex_lock(&sim->stop_mutex);
	if (sim->stop)
	{
		pthread_mutex_unlock(&sim->stop_mutex);
		return ;
	}
	pthread_mutex_lock(&sim->print_mutex);
	ts = sim_timestamp_ms(sim);
	printf("%ld %d %s\n", ts, philo->id, msg);
	pthread_mutex_unlock(&sim->print_mutex);
	pthread_mutex_unlock(&sim->stop_mutex);
}

static void	philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->mutex);
	philo_log(philo, "has taken a fork");
	pthread_mutex_lock(&philo->second_fork->mutex);
	philo_log(philo, "has taken a fork");
}

static void	philo_eat(t_philo *philo)
{
	t_sim	*sim;

	sim = philo->sim;
	philo_take_forks(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_ms = now_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	philo_log(philo, "is eating");
	smart_usleep(sim->time_to_eat, sim);
	pthread_mutex_unlock(&philo->first_fork->mutex);
	pthread_mutex_unlock(&philo->second_fork->mutex);
}

static void	philo_sleep_and_think(t_philo *philo)
{
	philo_log(philo, "is sleeping");
	smart_usleep(philo->sim->time_to_sleep, philo->sim);
	philo_log(philo, "is thinking");
}

void	*philo_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->sim->num_philo == 1)
	{
		pthread_mutex_lock(&philo->first_fork->mutex);
		philo_log(philo, "has taken a fork");
		while (!sim_is_stopped(philo->sim))
			smart_usleep(1, philo->sim);
		pthread_mutex_unlock(&philo->first_fork->mutex);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!sim_is_stopped(philo->sim))
	{
		philo_eat(philo);
		if (philo->sim->must_eat > 0
			&& philo->meals_eaten >= philo->sim->must_eat)
			break ;
		philo_sleep_and_think(philo);
	}
	return (NULL);
}
