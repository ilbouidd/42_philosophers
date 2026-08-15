/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbouidd <ilbouidd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 14:20:40 by ilbouidd          #+#    #+#             */
/*   Updated: 2026/08/15 12:35:42 by ilbouidd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_finished(t_all *data)
{
	int	end;

	pthread_mutex_lock(&data->end_mutex);
	end = data->end;
	pthread_mutex_unlock(&data->end_mutex);
	return (end);
}

int	philo_dead(t_philo *philo)
{
	long	now;
	long	last_meal;

	pthread_mutex_lock(&philo->data->meal_mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	now = get_time_ms();
	if (now - last_meal < (long)philo->data->time_die)
		return (0);
	pthread_mutex_lock(&philo->data->end_mutex);
	if (philo->data->end)
	{
		pthread_mutex_unlock(&philo->data->end_mutex);
		return (1);
	}
	philo->data->end = 1;
	pthread_mutex_unlock(&philo->data->end_mutex);
	print_value(philo, "died");
	return (1);
}

static int	good_time_must_eat(t_all *data)
{
	int	i;
	int	is_good;

	if (data->time_must_eat <= 0)
		return (0);
	i = 0;
	is_good = 0;
	pthread_mutex_lock(&data->meal_mutex);
	while (i < data->nb_philo)
	{
		if (data->philo[i].meals >= data->time_must_eat)
			is_good++;
		i++;
	}
	pthread_mutex_unlock(&data->meal_mutex);
	if (is_good == data->nb_philo)
	{
		pthread_mutex_lock(&data->end_mutex);
		data->end = 1;
		pthread_mutex_unlock(&data->end_mutex);
		return (1);
	}
	return (0);
}

void	server(t_all *data)
{
	int	i;

	while (!is_finished(data))
	{
		i = 0;
		if (good_time_must_eat(data))
			return ;
		while (i < data->nb_philo)
		{
			if (philo_dead(&data->philo[i]))
				return ;
			i++;
		}
		usleep(500);
	}
}
