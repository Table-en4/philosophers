/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:31:02 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/17 19:23:08 by molapoug         ###   ########.fr       */
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

	p = (t_philo *)arg;
	pthread_mutex_lock(&p->data->death_mutex);
	p->last_meal_time = get_time();
	p->meals_eaten = 0;
	pthread_mutex_unlock(&p->data->death_mutex);
	if (p->id % 2 == 0)
		ft_usleep(p->data->time_to_die / 2, p->data);
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
			ft_usleep(p->data->time_to_eat, p->data);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)arg;
	while (!is_dead(philos[0].data))
	{
		i = 0;
		while (i < philos[0].data->nb_philo)
		{
			if (check_death(&philos[i]))
			{
				print_philo(&philos[i], "died");
				set_death(philos[0].data);
				return (NULL);
			}
			i++;
		}
		ft_usleep(1000, philos->data);
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
		pthread_create(&philos[i].thread, NULL, thread_routine, &philos[i]);
		i++;
	}
	pthread_create(monitor, NULL, monitor_routine, philos);
	return (0);
}

void	join_all_threads(t_philo *philos, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
		pthread_join(philos[i++].thread, NULL);
}
