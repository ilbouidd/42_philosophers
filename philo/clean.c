/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbouidd <ilbouidd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:36:53 by ilbouidd          #+#    #+#             */
/*   Updated: 2026/09/03 09:31:54 by ilbouidd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_all *data)
{
	if (!data)
		return ;
	if (data->fork_taken)
		free(data->fork_taken);
	if (data->fork_turn)
		free(data->fork_turn);
	if (data->philo_waiting)
		free(data->philo_waiting);
	if (data->philo)
		free(data->philo);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->end_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->forks_lock);
}
