/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbouidd <ilbouidd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 14:20:40 by ilbouidd          #+#    #+#             */
/*   Updated: 2026/04/17 10:51:08 by ilbouidd         ###   ########.fr       */
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

static int	philo_dead(t_philo *philo)
{
	long	now;
	long	last_meal;

	pthread_mutex_lock(&philo->data->meal_mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	now = get_time_ms();
	if (now - last_meal >= (long)philo->data->time_die)
	{
		pthread_mutex_lock(&philo->data->end_mutex);
		philo->data->end = 1;
		pthread_mutex_unlock(&philo->data->end_mutex);
		pthread_mutex_lock(&philo->data->print);
		printf("%ld %d died\n", timestamp_ms(philo->data), philo->id);
		pthread_mutex_unlock(&philo->data->print);
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
		while (i < data->nb_philo)
		{
			if (philo_dead(&data->philo[i]))
				return ;
			i++;
		}
		usleep(500);
	}
}
