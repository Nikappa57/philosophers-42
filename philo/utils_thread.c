#include "philo.h"

// test
void	run_sync(void (*func)(void *), void *arg, pthread_mutex_t *sync)
{
	pthread_mutex_lock(sync);
	func(arg);
	pthread_mutex_unlock(sync);
}

void	change_philo_status(t_philo *philo, t_status status)
{
	pthread_mutex_lock(&philo->modify);
	philo->status = status;
	pthread_mutex_unlock(&philo->modify);
	pthread_mutex_lock(&philo->data->output);
	printf("%zu %d ", get_time() - philo->data->start, philo->id);
	if (status == EATING)
		printf("is eating\n");
	else if (status == SLEEPING)
		printf("is sleeping\n");
	else if (status == THINKING)
		printf("is thinking\n");
	else if (status == DIED)
		printf("died\n");
	pthread_mutex_unlock(&philo->data->output);
}

int	start_threads(t_data *data)
{
	int		i;

	i = 0;
	data->start = get_time();
	while (i < data->philo_n)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&philo_routine, &data->philos[i]))
			return (1);
		i++;
	}
	// if (pthread_create(&data->checker, NULL, &checker_routine, data))
	// 	return (1);
	return (0);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (1);
		i++;
	}
	// if (pthread_join(data->checker, NULL))
	// 	return (1);
	return (0);
}