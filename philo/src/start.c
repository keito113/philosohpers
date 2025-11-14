/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:32:26 by keitabe           #+#    #+#             */
/*   Updated: 2025/11/14 16:08:55 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_created_philos(t_sim *sim, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(sim->philos[i].thread, NULL);
		i++;
	}
}

// int	sim_start(t_sim *sim)
// {
// 	int	i;

// 	sim->start_ms = now_ms();
// 	if (sim->start_ms < 0)
// 		return (1);
// 	i = 0;
// 	while (i < sim->num_philo)
// 	{
// 		sim->philos[i].last_meal_ms = sim->start_ms;
// 		if (pthread_create(&sim->philos[i].thread, NULL, philo_thread,
// 				&sim->philos[i]) != 0)
// 		{
// 			sim_set_stop(sim);
// 			join_created_philos(sim, i);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	if (pthread_create(&sim->monitor_thread, NULL, monitor_thread, sim) != 0)
// 	{
// 		sim_set_stop(sim);
// 		join_created_philos(sim, sim->num_philo);
// 		return (1);
// 	}
// 	return (0);
// }
