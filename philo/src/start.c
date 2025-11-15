/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:32:26 by keitabe           #+#    #+#             */
/*   Updated: 2025/11/15 10:19:30 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sim_start(t_sim *sim, pthread_t *monitor)
{
	sim->start_ms = now_ms();
	if (sim->start_ms < 0)
		return (1);
	return (sim_start_threads(sim, monitor));
}
