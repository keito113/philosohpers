/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fairness.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:05:13 by keitabe           #+#    #+#             */
/*   Updated: 2025/11/28 17:14:25 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sim_init_groups(t_sim *sim)
{
	if (sim->num_philo % 2 == 0)
	{
		sim->target_in_group[0] = sim->num_philo / 2;
		sim->target_in_group[1] = sim->num_philo / 2;
	}
	else
	{
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
		if (need_group_flip(sim))
		{
			sim->entered_in_group[0] = 0;
			sim->entered_in_group[1] = 0;
			sim->current_group ^= 1;
		}
		if (can_enter_room_now(sim, philo))
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
