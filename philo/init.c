#include "philo.h"

/*
Checks if the input is valid
and returns 1 if it is not, 0 otherwise.

@param argc: the number of arguments
@param argv: the arguments
*/
int	check_input(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (1);
	i = 1;
	while (i < argc)
		if (!ft_isstrdigit(argv[i++]))
			return (1);
	return (0);
}

static int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
		pthread_mutex_init(&data->forks[i++], NULL);
	return (0);
}

static int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
	{
		data->philos[i].id = i + 1;
		// printf("philos n %d: ", data->philos[i].id);
		data->philos[i].meals = 0;
		data->philos[i].last_eat = get_time();
		data->philos[i].status = THINKING;
		data->philos[i].fork_left = &data->forks[i];
		data->philos[i].fork_right = &data->forks[(i + 1) % data->philo_n];
		data->philos[i].data = data;
		// printf("forks: %d - %d\n", i, (i + 1) % data->philo_n);
		pthread_mutex_init(&data->philos[i].status_mutex, NULL);
		pthread_mutex_init(&data->philos[i].meals_mutex, NULL);
		i++;
	}
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->philo_n = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->all_alive = 1;
	if (argc == 6)
		data->meals_n = ft_atoi(argv[5]);
	else
		data->meals_n = -1;
	if (data->philo_n < 1)
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->philo_n);
	if (!data->philos)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_n);
	if (!data->forks)
		return (1);
	pthread_mutex_init(&data->output, NULL);
	pthread_mutex_init(&data->all_alive_mutex, NULL);
	return (!data->forks || init_forks(data) || init_philos(data));
}
