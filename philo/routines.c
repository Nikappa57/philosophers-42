/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzogaudino <lorenzogaudino@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:12:41 by lorenzogaud       #+#    #+#             */
/*   Updated: 2024/02/26 23:45:24 by lorenzogaud      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	if (is_all_alive(philo->data) && get_philo_status(philo) != DIED)
		sync_print("has taken a fork", philo);
	else
	{
		pthread_mutex_unlock(philo->fork_left);
		return ;
	}
	pthread_mutex_lock(philo->fork_right);
	if (is_all_alive(philo->data) && get_philo_status(philo) != DIED)
		sync_print("has taken a fork", philo);
	else
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return ;
	}
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
}

void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_mutex);
	philo->last_eat = get_time();
	philo->meals++;
	pthread_mutex_unlock(&philo->meals_mutex);
}

void	p_eat(t_philo *philo)
{
	take_forks(philo);
	if (!is_all_alive(philo->data) || get_philo_status(philo) == DIED)
	{
		release_forks(philo);
		return ;
	}
	change_philo_status(philo, EATING);
	update_last_meal(philo);
	ft_usleep(philo->data->time_to_eat);
	release_forks(philo);
}

void	p_sleep(t_philo *philo)
{
	change_philo_status(philo, SLEEPING);
	ft_usleep(philo->data->time_to_sleep);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2)
		ft_usleep(philo->data->time_to_eat / 2);
	while (is_all_alive(data) && get_philo_status(philo) != DIED)
	{
		if (data->meals_n != -1 && philo->meals >= data->meals_n)
		{
			change_philo_status(philo, THINKING);
			break ;
		}
		if (get_philo_status(philo) == THINKING)
			p_eat(philo);
		else if (get_philo_status(philo) == EATING)
			p_sleep(philo);
		else if (get_philo_status(philo) == SLEEPING)
			change_philo_status(philo, THINKING);
	}
	return (NULL);
}
