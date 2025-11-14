/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:27:08 by keitabe           #+#    #+#             */
/*   Updated: 2025/11/14 12:27:53 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_parse(const char *s, int *i)
{
	if (!s || !*s)
		return (0);
	*i = 0;
	if (s[*i] == '+')
		(*i)++;
	if (!s[*i])
		return (0);
	return (1);
}

int	parse_positive_int(const char *s, int *out)
{
	int	i;
	int	acc;
	int	d;

	if (!init_parse(s, &i))
		return (0);
	acc = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		d = s[i] - '0';
		if (acc > INT_MAX / 10 || (acc == INT_MAX / 10 && d > INT_MAX % 10))
			return (0);
		acc = acc * 10 + d;
		i++;
	}
	if (acc <= 0)
		return (0);
	*out = acc;
	return (1);
}
