/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fairness.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:05:13 by keitabe           #+#    #+#             */
/*   Updated: 2025/11/24 14:36:36 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	max_long(long a, long b)
{
	if (a > b)
		return (a);
	return (b);
}

void	sim_calc_safe_time_to_die(t_sim *sim)
{
	long	even_base;
	long	odd_base;

	even_base = max_long(2 * sim->time_to_eat, sim->time_to_eat
			+ sim->time_to_sleep);
	odd_base = max_long(3 * sim->time_to_eat, sim->time_to_eat
			+ sim->time_to_sleep);
	if (sim->num_philo % 2 == 0)
	{
		sim->safe_time_to_die = even_base + 10;
		sim->target_in_group[0] = sim->num_philo / 2;
		sim->target_in_group[1] = sim->num_philo / 2;
	}
	else
	{
		sim->safe_time_to_die = odd_base + 10;
		sim->target_in_group[1] = (sim->num_philo + 1) / 2;
		sim->target_in_group[0] = sim->num_philo / 2;
	}
	sim->entered_in_group[0] = 0;
	sim->entered_in_group[1] = 0;
	sim->current_group = 1;
}

int	enter_room(t_philo *philo)
{
	t_sim	*sim;

	sim = philo->sim;
	while (!sim_is_stopped(sim))
	{
		pthread_mutex_lock(&sim->room_mutex);
		if (sim->entered_in_group[sim->current_group] >= sim->target_in_group[sim->current_group])
		{
			sim->entered_in_group[0] = 0;
			sim->entered_in_group[1] = 0;
			sim->current_group ^= 1;
		}
		if (philo->group == sim->current_group
			&& sim->entered_in_group[sim->current_group] < sim->target_in_group[sim->current_group]
			&& sim->in_room < sim->num_philo - 1)
		{
			sim->entered_in_group[sim->current_group]++;
			sim->in_room++;
			pthread_mutex_unlock(&sim->room_mutex);
			return (1);
		}
		pthread_mutex_unlock(&sim->room_mutex);
		smart_usleep(1, sim);
	}
	return (0);
}

void	leave_room(t_philo *philo)
{
	t_sim	*sim;

	sim = philo->sim;
	pthread_mutex_lock(&sim->room_mutex);
	sim->in_room--;
	pthread_mutex_unlock(&sim->room_mutex);
}

int	philo_is_full(t_philo *philo)
{
	t_sim	*sim;
	int		full;

	sim = philo->sim;
	if (sim->must_eat <= 0)
		return (0);
	pthread_mutex_lock(&philo->meal_mutex);
	full = (philo->meals_eaten >= sim->must_eat);
	pthread_mutex_unlock(&philo->meal_mutex);
	return (full);
}
