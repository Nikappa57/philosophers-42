#include "philo.h"

void	sync_print(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->output);
	if (is_all_alive(philo->data))
	{
		printf("%zu %d ", get_time() - philo->data->start, philo->id);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&philo->data->output);
}

void	change_philo_status(t_philo *philo, t_status status)
{
	pthread_mutex_lock(&philo->status_mutex);
	philo->status = status;
	pthread_mutex_unlock(&philo->status_mutex);
	if (status == EATING)
		sync_print("is eating", philo);
	else if (status == SLEEPING)
		sync_print("is sleeping", philo);
	else if (status == THINKING)
		sync_print("is thinking", philo);
	else if (status == DIED)
		sync_print("died", philo);
}

t_status	get_philo_status(t_philo *philo)
{
	t_status	status;

	pthread_mutex_lock(&philo->status_mutex);
	status = philo->status;
	pthread_mutex_unlock(&philo->status_mutex);
	return (status);
}

int	start_threads(t_data *data)
{
	int		i;

	i = 0;
	data->start = get_time();
	if (pthread_create(&data->checker, NULL, &checker_routine, data))
		return (1);
	while (i < data->philo_n)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&philo_routine, &data->philos[i]))
			return (1);
		i++;
	}
	return (0);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
		if (pthread_join(data->philos[i++].thread, NULL))
			return (1);
	if (pthread_join(data->checker, NULL))
		return (1);
	return (0);
}
