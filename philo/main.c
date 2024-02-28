/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzogaudino <lorenzogaudino@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:16:50 by lorenzogaud       #+#    #+#             */
/*   Updated: 2024/02/29 00:17:09 by lorenzogaud      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	data.meals_n = -1;
	data.philos = NULL;
	data.forks = NULL;
	data.philo_n = 0;
	data.all_alive = 1;
	if (check_input(argc, argv))
		return (1);
	if (init_data(&data, argc, argv))
		return (clear_data(&data), 1);
	if (start_threads(&data))
		return (clear_data(&data), 1);
	if (join_threads(&data))
		return (clear_data(&data), 1);
	return (clear_data(&data), 1);
}
