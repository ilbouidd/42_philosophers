/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbouidd <ilbouidd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 08:48:35 by ilbouidd          #+#    #+#             */
/*   Updated: 2026/04/13 00:12:58 by ilbouidd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	no_cara(char **av)
{
	int	i;
	int	j;

	i = 1;
	if (!av || !av[i])
		return (1);
	while (av[i])
	{
		j = 0;
		if (av[i][0] == '\0')
			return (1);
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	errors_all(t_all *data)
{
	if (no_cara(data->av))
		return (printf("Error: characters in argument\n"), 1);
	if (data->nb_philo <= 0)
		return (printf("Error: no good number of philosophers\n"), 1);
	if (data->time_die <= 0)
		return (printf("Error: no good time for die\n"), 1);
	if (data->time_eat <= 0)
		return (printf("Error: no good time for eat\n"), 1);
	if (data->time_sleep <= 0)
		return (printf("Error: no good time for sleep\n"), 1);
	if (data->ac == 6 && data->time_must_eat <= 0)
		return (printf("Error: no good must_eat value\n"), 1);
	return (0);
}
