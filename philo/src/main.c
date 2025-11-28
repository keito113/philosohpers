/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:11:40 by keitabe           #+#    #+#             */
/*   Updated: 2025/11/28 17:12:34 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	run_simulation(t_sim *sim, pthread_t *monitor, int *stage)
{
	if (init_sim(sim) != 0)
		return (1);
	*stage = INIT_SIM_MUTEX;
	if (init_forks(sim) != 0)
		return (1);
	*stage = INIT_FORKS;
	if (init_philos(sim) != 0)
		return (1);
	*stage = INIT_PHILOS;
	sim_init_groups(sim);
	if (sim_start(sim, monitor) != 0)
		return (1);
	return (0);
}

static void	join_thread_and_cleanup(t_sim *sim, pthread_t monitor, int stage)
{
	int	i;

	pthread_join(monitor, NULL);
	i = 0;
	while (i < sim->num_philo)
	{
		pthread_join(sim->philos[i].thread, NULL);
		i++;
	}
	destroy_all(sim, stage);
}

int	main(int ac, char **av)
{
	t_sim		sim;
	pthread_t	monitor;
	int			stage;

	stage = INIT_NONE;
	if (parse_args(ac, av, &sim) != 0)
		return (1);
	if (run_simulation(&sim, &monitor, &stage) != 0)
	{
		destroy_all(&sim, stage);
		return (1);
	}
	join_thread_and_cleanup(&sim, monitor, stage);
	return (0);
}
