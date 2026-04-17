/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbouidd <ilbouidd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 14:12:54 by ilbouidd          #+#    #+#             */
/*   Updated: 2026/04/17 11:53:13 by ilbouidd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_value(philo, "fork");
		pthread_mutex_lock(philo->right_fork);
		print_value(philo, "fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_value(philo, "fork");
		pthread_mutex_lock(philo->left_fork);
		print_value(philo, "fork");
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = get_time_ms();
	philo->meals++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_value(philo, "eat");
	ft_usleep(philo->data->time_eat, philo->data);
	drop_forks(philo);
}

void	eat_sleep_think(t_philo *philo)
{
	eat(philo);
	print_value(philo, "sleep");
	ft_usleep(philo->data->time_sleep, philo->data);
	print_value(philo, "think");
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(1000);
	while (!is_finished(philo->data))
	{
		eat_sleep_think(philo);
		if (philo->data->time_must_eat > 0
			&& philo->meals >= philo->data->time_must_eat)
			break ;
	}
	return (NULL);
}
