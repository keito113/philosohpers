/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:28:05 by keitabe           #+#    #+#             */
/*   Updated: 2025/11/28 17:12:23 by keitabe          ###   ########.fr       */
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

# define INIT_NONE 0
# define INIT_SIM_MUTEX 1
# define INIT_FORKS 2
# define INIT_PHILOS 3

typedef struct s_sim	t_sim;

typedef struct s_fork
{
	pthread_mutex_t		mutex;
}						t_fork;

typedef struct s_philo
{
	int					id;
	int					group;
	pthread_t			thread;
	int					meals_eaten;
	pthread_mutex_t		meal_mutex;
	long long			last_meal_ms;
	t_fork				*first_fork;
	t_fork				*second_fork;
	t_sim				*sim;
}						t_philo;

struct					s_sim
{
	int					num_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					target_in_group[2];
	int					entered_in_group[2];
	int					must_eat;
	long				start_ms;
	int					stop;
	int					in_room;
	int					current_group;
	pthread_mutex_t		stop_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		room_mutex;
	t_fork				*forks;
	t_philo				*philos;
};

// init.c
int						init_sim(t_sim *sim);
int						init_forks(t_sim *sim);
int						init_philos(t_sim *sim);

// parse_utils.c
int						parse_positive_int(const char *s, int *out);

// parse
int						parse_args(int ac, char **av, t_sim *sim);

// time.c
long					now_ms(void);
long					sim_timestamp_ms(t_sim *sim);
int						sim_is_stopped(t_sim *sim);
void					smart_usleep(long ms, t_sim *sim);

// util.c
void					sim_set_stop(t_sim *sim);
int						need_group_flip(t_sim *sim);
int						can_enter_room_now(t_sim *sim, t_philo *philo);

// monitor.c
void					*monitor_thread(void *arg);
int						sim_start_threads(t_sim *sim, pthread_t *monitor);

// routine.c
void					philo_routine(t_philo *philo);

// philo_thread.c
void					philo_log_die(t_philo *philo);
void					philo_log(t_philo *philo, const char *msg);
void					*philo_thread(void *arg);

// start.c
int						sim_start(t_sim *sim, pthread_t *monitor);

// fairness.c
void					sim_init_groups(t_sim *sim);
int						enter_room(t_philo *philo);
void					leave_room(t_philo *philo);
int						philo_is_full(t_philo *philo);

// cleanup.c
void					destroy_forks(t_sim *sim, int n);
void					destroy_philos(t_sim *sim, int n);
void					destroy_sim_mutex(t_sim *sim);
void					destroy_all(t_sim *sim, int stage);

#endif
