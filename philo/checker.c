#include "philo.h"

static void	philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->all_alive_mutex);
	pthread_mutex_lock(&philo->status_mutex);
	printf("%zu %d died\n", get_time() - philo->data->start, philo->id);
	philo->data->all_alive = 0;
	philo->status = DIED;
	pthread_mutex_unlock(&philo->status_mutex);
	pthread_mutex_unlock(&philo->data->all_alive_mutex);
	release_forks(philo);
}

int	is_all_alive(t_data *data)
{
	int	all_alive;

	pthread_mutex_lock(&data->all_alive_mutex);
	all_alive = data->all_alive;
	pthread_mutex_unlock(&data->all_alive_mutex);
	return (all_alive);
}

void	*checker_routine(void *arg)
{
	t_data	*data;
	int		check;
	int		i;
	t_philo	*philo;

	data = (t_data *)arg;
	check = 0;
	i = 0;
	while (data->meals_n == -1 || check < data->philo_n)
	{
		if (i == data->philo_n)
			i = 0;
		philo = &data->philos[i++];
		pthread_mutex_lock(&philo->meals_mutex);
		if (get_time() - philo->last_eat > data->time_to_die)
		{
			philo_dead(philo);
			pthread_mutex_unlock(&philo->meals_mutex);
			break ;
		}
		if (data->meals_n != -1 && philo->meals >= data->meals_n)
			check++;
		pthread_mutex_unlock(&philo->meals_mutex);
		usleep(500);
	}
	return (NULL);
}
