/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzogaudino <lorenzogaudino@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:16:50 by lorenzogaud       #+#    #+#             */
/*   Updated: 2024/02/24 00:00:20 by lorenzogaud      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

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
