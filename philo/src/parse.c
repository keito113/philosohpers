/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:30:37 by keitabe           #+#    #+#             */
/*   Updated: 2025/11/14 12:39:28 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	print_usage(void)
{
	printf("Usage: ./philo philo die eat sleep [must_eat]\n");
	printf("constraints: philo=1...200, time=1...2147483647, must_eat>=1\n");
	return (1);
}

static int	error_args(char **av, t_sim *sim)
{
	int	tmp;

	if (!parse_positive_int(av[1], &tmp))
		return (0);
	sim->num_philo = tmp;
	if (!parse_positive_int(av[2], &tmp))
		return (0);
	sim->time_to_die = tmp;
	if (!parse_positive_int(av[3], &tmp))
		return (0);
	sim->time_to_eat = tmp;
	if (!parse_positive_int(av[4], &tmp))
		return (0);
	sim->time_to_sleep = tmp;
	return (1);
}

static int	parse_must_eat(char *s, t_sim *sim)
{
	int	tmp;

	if (!parse_positive_int(s, &tmp))
		return (0);
	sim->must_eat = tmp;
	return (1);
}

static int	validate_range(t_sim *sim)
{
	if (sim->num_philo < 1 || sim->num_philo > 200)
		return (0);
	if (sim->time_to_die < 1 || sim->time_to_eat < 1 || sim->time_to_sleep < 1)
		return (0);
	if (sim->must_eat != -1 && sim->must_eat < 1)
		return (0);
	return (1);
}

int	parse_args(int ac, char **av, t_sim *sim)
{
	if (ac != 5 && ac != 6)
		return (print_usage());
	if (!error_args(av, sim))
		return (print_usage());
	sim->must_eat = -1;
	if (ac == 6 && !parse_must_eat(av[5], sim))
		return (print_usage());
	if (!validate_range(sim))
		return (print_usage());
	return (0);
}
