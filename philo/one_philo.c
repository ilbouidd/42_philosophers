/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbouidd <ilbouidd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 15:56:11 by ilbouidd          #+#    #+#             */
/*   Updated: 2026/04/17 10:51:31 by ilbouidd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_philo *philo)
{
	print_value(philo, "fork");
	ft_usleep(philo->data->time_die, philo->data);
	pthread_mutex_lock(&philo->data->end_mutex);
	philo->data->end = 1;
	pthread_mutex_unlock(&philo->data->end_mutex);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d died\n", timestamp_ms(philo->data), philo->id);
	pthread_mutex_unlock(&philo->data->print);
}
