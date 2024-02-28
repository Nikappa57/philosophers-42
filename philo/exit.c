#include "philo.h"

void	clear_data(t_data *data)
{
	int		i;
	t_philo	*philo;

	if (data->checker)
		pthread_detach(data->checker);
	if (data->philos)
	{
		i = 0;
		while (i < data->philo_n)
		{
			philo = &data->philos[i];
			pthread_mutex_destroy(&philo->status_mutex);
			i++;
		}
		free(data->philos);
		pthread_mutex_destroy(&data->output);
		pthread_mutex_destroy(&data->all_alive_mutex);
	}
	if (data->forks)
	{
		i = 0;
		while (i < data->philo_n)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
	}
}
