/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbouidd <ilbouidd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 09:32:03 by ilbouidd          #+#    #+#             */
/*   Updated: 2026/09/03 11:41:31 by ilbouidd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fork_available(t_all *data, t_philo *philo, int fork, int rival)
{
	if (data->fork_taken[fork])
		return (0);
	if (data->fork_turn[fork] == 0 || data->fork_turn[fork] == philo->id)
		return (1);
	return (!data->philo_waiting[rival]);
}

int	forks_free(t_philo *philo)
{
	t_all	*data;
	int		my_idx;
	int		left_rival;

	data = philo->data;
	my_idx = philo->id - 1;
	left_rival = (my_idx - 1 + data->nb_philo) % data->nb_philo;
	return (fork_available(data, philo, philo->left_fork, left_rival)
		&& fork_available(data, philo, philo->right_fork, philo->right_fork));
}

int	try_take_forks(t_philo *philo)
{
	t_all	*data;
	int		got;
	int		my_idx;

	data = philo->data;
	my_idx = philo->id - 1;
	pthread_mutex_lock(&data->forks_lock);
	data->philo_waiting[my_idx] = 1;
	got = forks_free(philo);
	if (got)
	{
		data->fork_taken[philo->left_fork] = 1;
		data->fork_taken[philo->right_fork] = 1;
		data->philo_waiting[my_idx] = 0;
	}
	pthread_mutex_unlock(&data->forks_lock);
	return (got);
}

int	take_forks(t_philo *philo)
{
	int	got;

	got = try_take_forks(philo);
	while (!got && !is_finished(philo->data))
	{
		usleep(100);
		got = try_take_forks(philo);
	}
	if (!got)
	{
		pthread_mutex_lock(&philo->data->forks_lock);
		philo->data->philo_waiting[philo->id - 1] = 0;
		pthread_mutex_unlock(&philo->data->forks_lock);
	}
	else
	{
		print_value(philo, "fork");
		print_value(philo, "fork");
	}
	return (got);
}

void	drop_forks(t_philo *philo)
{
	t_all	*data;
	int		left_rival;

	data = philo->data;
	left_rival = (philo->id - 2 + data->nb_philo) % data->nb_philo;
	pthread_mutex_lock(&data->forks_lock);
	data->fork_taken[philo->left_fork] = 0;
	data->fork_taken[philo->right_fork] = 0;
	data->fork_turn[philo->left_fork] = left_rival + 1;
	data->fork_turn[philo->right_fork] = philo->right_fork + 1;
	pthread_mutex_unlock(&data->forks_lock);
}
