/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 10:06:05 by keitabe           #+#    #+#             */
/*   Updated: 2025/11/19 15:57:08 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_log_die(t_philo *philo)
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
	sim->stop = 1;
	pthread_mutex_lock(&sim->print_mutex);
	ts = sim_timestamp_ms(sim);
	if (ts >= 0)
		printf("%ld %d died\n", ts, philo->id);
	pthread_mutex_unlock(&sim->print_mutex);
	pthread_mutex_unlock(&sim->stop_mutex);
}

void	philo_log(t_philo *philo, const char *msg)
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
	if (ts >= 0)
		printf("%ld %d %s\n", ts, philo->id, msg);
	pthread_mutex_unlock(&sim->print_mutex);
	pthread_mutex_unlock(&sim->stop_mutex);
}

void	*philo_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo_routine(philo);
	return (NULL);
}
