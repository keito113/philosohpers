/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:24:03 by keitabe           #+#    #+#             */
/*   Updated: 2025/11/15 17:26:43 by keitabe          ###   ########.fr       */
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
