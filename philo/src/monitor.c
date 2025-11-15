/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:53:23 by keitabe           #+#    #+#             */
/*   Updated: 2025/11/15 15:26:09 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_created_philos(t_sim *sim, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(sim->philos[i].thread, NULL);
		i++;
	}
}

static int	all_philos_full(t_sim *sim)
{
	int	i;

	if (sim->must_eat <= 0)
		return (0);
	pthread_mutex_lock(&sim->stop_mutex);
	i = 0;
	while (i < sim->num_philo)
	{
		if (sim->philos[i].meals_eaten < sim->must_eat)
		{
			pthread_mutex_unlock(&sim->stop_mutex);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&sim->stop_mutex);
	return (1);
}

static int	check_philo_dead(t_philo *philo)
{
	t_sim	*sim;
	long	now;
	long	diff;

	sim = philo->sim;
	now = now_ms();
	diff = now - philo->last_meal_ms;
	if (diff <= sim->time_to_die || sim->stop)
	{
		pthread_mutex_unlock(&sim->stop_mutex);
		return (0);
	}
	sim->stop = 1;
	pthread_mutex_lock(&sim->print_mutex);
	printf("%ld %d died\n", now - sim->start_ms, philo->id);
	pthread_mutex_unlock(&sim->print_mutex);
	pthread_mutex_unlock(&sim->stop_mutex);
	return (1);
}

void	*monitor_thread(void *arg)
{
	t_sim	*sim;
	int		i;

	sim = (t_sim *)arg;
	while (!sim_is_stopped(sim))
	{
		i = 0;
		while (i < sim->num_philo)
		{
			if (check_philo_dead(&sim->philos[i]))
				return (NULL);
			i++;
		}
		if (all_philos_full(sim))
		{
			sim_set_stop(sim);
			return (NULL);
		}
		smart_usleep(1, sim);
	}
	return (NULL);
}

int	sim_start_threads(t_sim *sim, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < sim->num_philo)
	{
		if (pthread_create(&sim->philos[i].thread, NULL, philo_thread,
				&sim->philos[i]) != 0)
		{
			sim_set_stop(sim);
			join_created_philos(sim, i);
			return (1);
		}
		i++;
	}
	if (pthread_create(monitor, NULL, monitor_thread, sim) != 0)
	{
		sim_set_stop(sim);
		join_created_philos(sim, sim->num_philo);
		return (1);
	}
	return (0);
}
