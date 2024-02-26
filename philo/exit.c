#include "philo.h"

void	clear_data(t_data *data)
{
	int	i;

	if (data->checker)
		pthread_detach(data->checker);
	if (data->philos)
	{
		i = 0;
		while (i < data->philo_n)
		{
			pthread_mutex_destroy(&data->philos[i].status_mutex);
			pthread_mutex_destroy(&data->philos[i].meals_mutex);
			i++;
		}
		free(data->philos);
	}
	if (data->forks)
		free(data->forks);
	return ;
}
