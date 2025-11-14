/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:00:41 by keitabe           #+#    #+#             */
/*   Updated: 2025/11/14 15:52:34 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	now_ms(void)
{
	struct timeval	tv;
	long			ms;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	ms = tv.tv_sec * 1000L + tv.tv_usec / 1000L;
	return (ms);
}

long	sim_timestamp_ms(t_sim *sim)
{
	long	now;

	now = now_ms();
	if (now == 0)
		return (0);
	return (now - sim->start_ms);
}

int	sim_is_stopped(t_sim *sim)
{
	int	value;

	pthread_mutex_lock(&sim->stop_mutex);
	value = sim->stop;
	pthread_mutex_unlock(&sim->stop_mutex);
	return (value);
}

void	smart_usleep(long ms, t_sim *sim)
{
	long	start;
	long	now;

	start = now_ms();
	if (start == 0)
		return ;
	while (!sim_is_stopped(sim))
	{
		now = now_ms();
		if (now == 0)
			break ;
		if (now - start >= ms)
			break ;
		usleep(200);
	}
}
