/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbouidd <ilbouidd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 08:33:14 by ilbouidd          #+#    #+#             */
/*   Updated: 2026/04/17 11:10:11 by ilbouidd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi_philo(const char *nptr)
{
	size_t	i;
	long	res;

	if (!nptr || nptr[0] == '\0')
		return (-1);
	i = 0;
	res = 0;
	while (nptr[i])
	{
		if (nptr[i] < '0' || nptr[i] > '9')
			return (-1);
		res = res * 10 + (nptr[i] - '0');
		if (res > INT_MAX)
			return (-1);
		i++;
	}
	return (res);
}

size_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

size_t	timestamp_ms(t_all *data)
{
	return (get_time_ms() - data->start_time);
}

void	ft_usleep(size_t time_ms, t_all *data)
{
	size_t	start;

	start = get_time_ms();
	while (!is_finished(data))
	{
		if ((get_time_ms() - start) >= (size_t)time_ms)
			break ;
		usleep(500);
	}
}
