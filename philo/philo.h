/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzogaudino <lorenzogaudino@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:21:41 by lorenzogaud       #+#    #+#             */
/*   Updated: 2024/02/29 00:21:05 by lorenzogaud      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	DIED
}	t_status;

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals;
	size_t			last_eat;
	t_status		status;
	pthread_t		thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	status_mutex;
	pthread_mutex_t	meals_mutex;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				philo_n;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_n;
	int				all_alive;
	size_t			start;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_t		checker;
	pthread_mutex_t	output;
	pthread_mutex_t	all_alive_mutex;
}	t_data;

/*  utils functions */

// str
int			ft_atoi(const char *str);
int			ft_isstrdigit(const char *s);

// time
size_t		get_time(void);
void		ft_usleep(size_t time);

// threads
void		print_status(t_philo *philo);
void		change_philo_status(t_philo *philo, t_status status);
void		sync_print(char *str, t_philo *philo);
void		take_forks(t_philo *philo);
int			start_threads(t_data *data);
void		update_last_meal(t_philo *philo);
int			join_threads(t_data *data);
t_status	get_philo_status(t_philo *philo);
int			is_all_alive(t_data *data);

/* init functions */

int			check_input(int argc, char **argv);
int			init_data(t_data *data, int argc, char **argv);

// exit functions

void		clear_data(t_data *data);

// routines functions

void		*philo_routine(void *arg);
void		*checker_routine(void *arg);
void		release_forks(t_philo *philo);


#endif