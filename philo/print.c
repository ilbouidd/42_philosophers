/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbouidd <ilbouidd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 06:39:33 by ilbouidd          #+#    #+#             */
/*   Updated: 2026/04/13 00:42:07 by ilbouidd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_str(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] == s2[i]);
}

void	print_value(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	if (is_finished(philo->data))
	{
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	if (is_str(str, "fork"))
		printf("%ld %d has taken a fork\n", timestamp_ms(philo->data), philo->id);
	else if (is_str(str, "eat"))
		printf("%ld %d is eating\n", timestamp_ms(philo->data), philo->id);
	else if (is_str(str, "sleep"))
		printf("%ld %d is sleeping\n", timestamp_ms(philo->data), philo->id);
	else if (is_str(str, "think"))
		printf("%ld %d is thinking\n", timestamp_ms(philo->data), philo->id);
	pthread_mutex_unlock(&philo->data->print);
}