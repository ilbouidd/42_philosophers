/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbouidd <ilbouidd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 14:38:35 by ilbouidd          #+#    #+#             */
/*   Updated: 2026/04/13 00:37:20 by ilbouidd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_all	t_all;

typedef struct s_philo
{
	int				id;
	int				meals;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_all			*data;
}	t_philo;

typedef struct s_all
{
	int				nb_philo;
	int				ac;
	char			**av;
	long			start_time;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			time_must_eat;
	int				end;
	pthread_mutex_t	print;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}	t_all;

long	ft_atoi_philo(const char *nptr);
int		errors_all(t_all *data);
void	init_all(t_all *data);

int		init_mutexes(t_all *data);
int		init_philos(t_all *data);
int		init_threads(t_all *data);

void	*routine(void *arg);
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
void	eat_sleep_think(t_philo *philo);

int		is_finished(t_all *data);
void	server(t_all *data);

long	get_time_ms(void);
long	timestamp_ms(t_all *data);
void	ft_usleep(size_t time_ms, t_all *data);

void	print_value(t_philo *philo, char *str);
void	destroy_all(t_all *data);

#endif