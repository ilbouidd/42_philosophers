/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbouidd <ilbouidd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:15:01 by ilbouidd          #+#    #+#             */
/*   Updated: 2026/04/13 00:35:43 by ilbouidd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_all(t_all *data)
{
	data->nb_philo = ft_atoi_philo(data->av[1]);
	data->time_die = ft_atoi_philo(data->av[2]);
	data->time_eat = ft_atoi_philo(data->av[3]);
	data->time_sleep = ft_atoi_philo(data->av[4]);
	data->time_must_eat = 0;
	data->end = 0;
	data->forks = NULL;
	data->philo = NULL;
	if (data->ac == 6)
		data->time_must_eat = ft_atoi_philo(data->av[5]);
}

int	init_mutexes(t_all *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	if (pthread_mutex_init(&data->print, NULL))
		return (1);
	if (pthread_mutex_init(&data->end_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->meal_mutex, NULL))
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

int	init_philos(t_all *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (1);
	data->start_time = get_time_ms();
	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals = 0;
		data->philo[i].last_meal = data->start_time;
		data->philo[i].data = data;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		i++;
	}
	return (0);
}

int	init_threads(t_all *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL,
				routine, &data->philo[i]))
			return (1);
		i++;
	}
	server(data);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	return (0);
}