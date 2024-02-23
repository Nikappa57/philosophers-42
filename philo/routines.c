#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	printf("philo %d\n", philo->id);
	while (philo->status != DIED && (data->meals_n == -1 || philo->meals < data->meals_n))
	{
		if (philo->status == THINKING)
		{
			change_philo_status(philo, DIED);
		}
	}

	return (NULL);
}
