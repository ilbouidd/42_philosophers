/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilbouidd <ilbouidd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 20:06:56 by ilbouidd          #+#    #+#             */
/*   Updated: 2026/04/11 14:39:34 by ilbouidd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_all	data;

	if (ac != 5 && ac != 6)
		return (printf("Error: No good arguments\n"), 1);
	data.av = av;
	data.ac = ac;
	init_all(&data);
	if (errors_all(&data))
		return (1);
	if (init_mutexes(&data))
		return (1);
	if (init_philos(&data))
		return (destroy_all(&data), 1);
	if (init_threads(&data))
		return (destroy_all(&data), 1);
	destroy_all(&data);
	return (0);
}
