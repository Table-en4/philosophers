/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:52:16 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/18 17:35:26 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_philo_death(t_philo *philos, int i)
{
	long	time;

	if (check_death(&philos[i]))
	{
		pthread_mutex_lock(&philos[0].data->print_mutex);
		if (!is_dead(philos[0].data))
		{
			time = get_time() - philos[0].data->start_time;
			printf("%ld %d died\n", time, philos[i].id);
		}
		pthread_mutex_unlock(&philos[0].data->print_mutex);
		set_death(philos[0].data);
		return (1);
	}
	return (0);
}

void	thinking_philo(t_philo *philo, void *arg)
{
	philo = (t_philo *)arg;
	philo->meals_eaten = 0;
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->death_mutex);
	if (philo->id % 2 == 1)
	{
		print_philo(philo, "is thinking");
		usleep(1000);
	}
}

int	take_fork_order(t_philo *philo)
{
	int	left;

	left = (philo->id - 1);
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_lock(&philo->data->forks[left]);
		print_philo(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die + 1, philo->data);
		pthread_mutex_unlock(&philo->data->forks[left]);
		return (1);
	}
	return (0);
}

int	check_philo_death_and_meals(t_philo *philos)
{
	int	i;
	int	full_count;

	i = 0;
	full_count = 0;
	while (i < philos[0].data->nb_philo)
	{
		if (handle_philo_death(philos, i))
			return (1);
		pthread_mutex_lock(&philos[i].meal_mutex);
		if (philos[0].data->nb_meals != -1
			&& philos[i].meals_eaten >= philos[0].data->nb_meals)
			full_count++;
		pthread_mutex_unlock(&philos[i].meal_mutex);
		i++;
	}
	if (philos[0].data->nb_meals != -1
		&& full_count == philos[0].data->nb_philo)
	{
		set_death(philos[0].data);
		return (1);
	}
	return (0);
}
