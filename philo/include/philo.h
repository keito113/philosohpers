/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:28:05 by keitabe           #+#    #+#             */
/*   Updated: 2025/11/15 17:28:26 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				id;
}					t_fork;

struct s_sim;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meals_eaten;
	pthread_mutex_t	meal_mutex;
	long long		last_meal_ms;
	t_fork			*first_fork;
	t_fork			*second_fork;
	struct s_sim	*sim;
}					t_philo;

typedef struct s_sim
{
	int				num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat;
	long			start_ms;
	int				stop;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	t_fork			*forks;
	t_philo			*philos;

}					t_sim;

// parse
int					parse_positive_int(const char *s, int *out);
int					parse_args(int ac, char **av, t_sim *sim);

// time.c
long				now_ms(void);
long				sim_timestamp_ms(t_sim *sim);
int					sim_is_stopped(t_sim *sim);
void				smart_usleep(long ms, t_sim *sim);

// util.c
void				sim_set_stop(t_sim *sim);

// log.c
void				*philo_thread(void *arg);

// monitor.c
void				*monitor_thread(void *arg);
int					sim_start_threads(t_sim *sim, pthread_t *monitor);

// start.c
int					sim_start(t_sim *sim, pthread_t *monitor);

// cleanup.c
void				destroy_forks(t_sim *sim, int n);
void				destroy_philos(t_sim *sim, int n);

#endif
