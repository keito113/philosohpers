/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 09:12:12 by keitabe           #+#    #+#             */
/*   Updated: 2025/11/18 13:23:50 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_handle_single(t_philo *philo)
{
	t_sim	*sim;

	sim = philo->sim;
	pthread_mutex_lock(&philo->first_fork->mutex);
	philo_log(philo, "has taken a fork");
	while (!sim_is_stopped(sim))
		usleep(1000);
	pthread_mutex_unlock(&philo->first_fork->mutex);
}

static void	philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->mutex);
	philo_log(philo, "has taken a fork");
	pthread_mutex_lock(&philo->second_fork->mutex);
	philo_log(philo, "has taken a fork");
}

static void	philo_eat(t_philo *philo)
{
	t_sim	*sim;

	sim = philo->sim;
	philo_take_forks(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_ms = now_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	philo_log(philo, "is eating");
	smart_usleep(sim->time_to_eat, sim);
	pthread_mutex_unlock(&philo->first_fork->mutex);
	pthread_mutex_unlock(&philo->second_fork->mutex);
}

static void	philo_sleep_and_think(t_philo *philo)
{
	t_sim	*sim;

	sim = philo->sim;
	philo_log(philo, "is sleeping");
	smart_usleep(sim->time_to_sleep, sim);
	philo_log(philo, "is thinking");
}

void	philo_routine(t_philo *philo)
{
	t_sim	*sim;

	sim = philo->sim;
	if (sim->num_philo == 1)
	{
		philo_handle_single(philo);
		return ;
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!sim_is_stopped(sim))
	{
		if (!enter_room(philo))
			break ;
		philo_eat(philo);
		leave_room(philo);
		if (philo_is_full(philo))
			break ;
		philo_sleep_and_think(philo);
	}
}
