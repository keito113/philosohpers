/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:42:54 by keitabe           #+#    #+#             */
/*   Updated: 2025/12/05 15:06:32 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_one_philo(t_sim *sim, int index, long long base_ms)
{
	t_philo	*philo;
	int		left;
	int		right;

	philo = &sim->philos[index];
	philo->id = index + 1;
	philo->group = philo->id % 2;
	philo->sim = sim;
	left = index;
	right = (index + 1) % sim->num_philo;
	if(left < right)
	{
		philo->first_fork = &sim->forks[left];
		philo->second_fork = &sim->forks[right];
	}
	else
	{
			philo->first_fork = &sim->forks[right];
		philo->second_fork = &sim->forks[left];
	}
	philo->meals_eaten = 0;
	philo->last_meal_ms = base_ms;
}

int	init_sim(t_sim *sim)
{
	sim->forks = NULL;
	sim->philos = NULL;
	sim->stop = 0;
	sim->in_room = 0;
	sim->current_group = 1;
	sim->entered_in_group[0] = 0;
	sim->entered_in_group[1] = 0;
	sim->target_in_group[0] = 0;
	sim->target_in_group[1] = 0;
	sim->start_ms = 0;
	if (pthread_mutex_init(&sim->print_mutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&sim->stop_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&sim->print_mutex);
		return (-1);
	}
	if (pthread_mutex_init(&sim->room_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&sim->stop_mutex);
		pthread_mutex_destroy(&sim->print_mutex);
		return (-1);
	}
	return (0);
}

int	init_forks(t_sim *sim)
{
	int	i;

	sim->forks = malloc(sizeof(t_fork) * sim->num_philo);
	if (!sim->forks)
		return (-1);
	i = 0;
	while (i < sim->num_philo)
	{
		if (pthread_mutex_init(&sim->forks[i].mutex, NULL) != 0)
		{
			destroy_forks(sim, i);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	init_philos(t_sim *sim)
{
	int		i;
	long	base_ms;

	sim->philos = malloc(sizeof(t_philo) * sim->num_philo);
	if (!sim->philos)
		return (-1);
	base_ms = now_ms();
	if (base_ms < 0)
	{
		free(sim->philos);
		sim->philos = NULL;
		return (-1);
	}
	i = 0;
	while (i < sim->num_philo)
	{
		init_one_philo(sim, i, base_ms);
		if (pthread_mutex_init(&sim->philos[i].meal_mutex, NULL) != 0)
		{
			destroy_philos(sim, i);
			return (-1);
		}
		i++;
	}
	return (0);
}
