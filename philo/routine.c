/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbouidd <ilbouidd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 14:12:54 by ilbouidd          #+#    #+#             */
/*   Updated: 2026/08/15 12:13:10 by ilbouidd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->left_fork < philo->right_fork)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(first);
	print_value(philo, "fork");
	pthread_mutex_lock(second);
	print_value(philo, "fork");
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
		if (meal_limit_reached(philo))
			break ;
		eat_sleep_think(philo);
	}
	return (NULL);
}