/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:24:03 by keitabe           #+#    #+#             */
/*   Updated: 2025/11/18 16:30:23 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks(t_sim *sim, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&sim->forks[i].mutex);
		i++;
	}
	free(sim->forks);
	sim->forks = NULL;
}

void	destroy_philos(t_sim *sim, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&sim->philos[i].meal_mutex);
		i++;
	}
	free(sim->philos);
	sim->philos = NULL;
}

void	destroy_sim_mutex(t_sim *sim)
{
	pthread_mutex_destroy(&sim->print_mutex);
	pthread_mutex_destroy(&sim->stop_mutex);
	pthread_mutex_destroy(&sim->room_mutex);
}

void	destroy_all(t_sim *sim, int stage)
{
	if (stage >= INIT_PHILOS)
		destroy_philos(sim, sim->num_philo);
	if (stage >= INIT_FORKS)
		destroy_forks(sim, sim->num_philo);
	if (stage >= INIT_SIM_MUTEX)
		destroy_sim_mutex(sim);
}
