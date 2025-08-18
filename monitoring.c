/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:31:02 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/18 17:36:10 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
}

void	*thread_routine(void *arg)
{
	t_philo	*p;
	int		extra_t_time;

	p = (t_philo *)arg;
	thinking_philo(p, arg);
	while (!is_dead(p->data))
	{
		philo_eat(p);
		if (p->data->nb_meals != -1 && p->meals_eaten >= p->data->nb_meals)
			break ;
		if (is_dead(p->data))
			break ;
		print_philo(p, "is sleeping");
		ft_usleep(p->data->time_to_sleep, p->data);
		if (is_dead(p->data))
			break ;
		print_philo(p, "is thinking");
		if (p->data->nb_philo % 2 == 1)
		{
			extra_t_time = (p->data->time_to_eat * 2) - p->data->time_to_sleep;
			if (extra_t_time > 0 && extra_t_time < p->data->time_to_die)
				ft_usleep(extra_t_time, p->data);
		}
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	usleep(1000);
	while (!is_dead(philos[0].data))
	{
		if (check_philo_death_and_meals(philos))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

int	create_thread(t_data *data, t_philo *philos, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		if (pthread_mutex_init(&philos[i].meal_mutex, NULL) != 0)
			return (1);
		if (pthread_create(&philos[i].thread, NULL, thread_routine, &philos[i]) == -1)
		{
			while (i-- > 0)
				pthread_join(philos[i].thread, NULL);
			return (1);
		}
		i++;
	}
	if (pthread_create(monitor, NULL, monitor_routine, philos) == -1)
		return (1);
	return (0);
}

void	join_all_threads(t_philo *philos, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
		pthread_join(philos[i++].thread, NULL);
}
