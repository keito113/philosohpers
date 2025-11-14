/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:53:23 by keitabe           #+#    #+#             */
/*   Updated: 2025/11/14 16:09:04 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static int	sim_start_threads(t_sim *sim, pthread_t *monitor)
// {
// 	int	i;

// 	i = 0;
// 	while (i < sim->num_philo)
// 	{
// 		if (pthread_create(&sim->philos[i].thread, NULL, philo_thread,
// 				&sim->philos[i]) != 0)
// 		{
// 			sim_set_stop(sim);
// 			join_created_philos(sim, i);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	if (pthread_create(monitor, NULL, monitor_thread, sim) != 0)
// 	{
// 		sim_set_stop(sim);
// 		join_created_philos(sim, sim->num_philo);
// 		return (1);
// 	}
// 	return (0);
// }
