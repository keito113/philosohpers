/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:50:19 by keitabe           #+#    #+#             */
/*   Updated: 2025/11/25 11:07:45 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sim_set_stop(t_sim *sim)
{
	pthread_mutex_lock(&sim->stop_mutex);
	sim->stop = 1;
	pthread_mutex_unlock(&sim->stop_mutex);
}

// fairness_utils
int	need_group_flip(t_sim *sim)
{
	int	group;
	int	entered;
	int	target;

	group = sim->current_group;
	entered = sim->entered_in_group[group];
	target = sim->target_in_group[group];
	if (entered >= target)
		return (1);
	return (0);
}

int	can_enter_room_now(t_sim *sim, t_philo *philo)
{
	int	group;
	int	entered;
	int	target;
	int	limit;

	group = sim->current_group;
	entered = sim->entered_in_group[group];
	target = sim->target_in_group[group];
	limit = sim->num_philo - 1;
	if (philo->group != group)
		return (0);
	if (entered >= target)
		return (0);
	if (sim->in_room >= limit)
		return (0);
	return (1);
}
