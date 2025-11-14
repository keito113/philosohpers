/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:42:54 by keitabe           #+#    #+#             */
/*   Updated: 2025/11/14 15:23:07 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_forks(t_sim *sim, int n)
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

static void	init_one_philo(t_sim *sim, int index, long long base_ms)
{
	t_philo	*philo;
	int		left;
	int		right;

	philo = &sim->philos[index];
	philo->id = index + 1;
	philo->sim = sim;
	left = index;
	right = (index + 1) % sim->num_philo;
	if (left < right)
	{
		philo->first_fork = left;
		philo->second_fork = right;
	}
	else
	{
		philo->first_fork = right;
		philo->second_fork = left;
	}
	philo->meals_eaten = 0;
	philo->last_meal_ms = base_ms;
}

int	init_sim(t_sim *sim)
{
	sim->forks = NULL;
	sim->philos = NULL;
	sim->stop = 0;
	if (pthread_mutex_init(&sim->print_mutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&sim->stop_mutex, NULL) != 0)
	{
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
		sim->forks[i].id = i;
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
	int			i;
	long long	base_ms;

	sim->philos = malloc(sizeof(t_philo) * sim->num_philo);
	if (!sim->philos)
		return (-1);
	base_ms = now_ms();
	if (base_ms == -1)
	{
		free(sim->philos);
		sim->philos = NULL;
		return (-1);
	}
	i = 0;
	while (i < sim->num_philo)
	{
		init_one_philo(sim, i, base_ms);
		i++;
	}
	return (0);
}
