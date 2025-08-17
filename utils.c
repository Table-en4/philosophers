/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:31:02 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/16 18:48:33 by molapoug         ###   ########.fr       */
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
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal_time = philo->data->start_time;
	philo->meals_eaten = 0;
	pthread_mutex_unlock(&philo->data->death_mutex);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat * 500);
	while (!is_dead(philo->data))
	{
		philo_eat(philo);
		if (philo->data->nb_meals != -1 && philo->meals_eaten >= philo->data->nb_meals)
			break ;
		if (is_dead(philo->data))
			break ;
		print_philo(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep * 1000);
		if (is_dead(philo->data))
			break ;
		print_philo(philo, "is thinking");
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
		ft_usleep(1000);
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

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}
