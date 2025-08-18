/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:48:33 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/18 11:17:36 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(t_philo *philo, char *msg)
{
	long	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!is_dead(philo->data))
	{
		time = get_time() - philo->data->start_time;
		printf("%ld %d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	take_forks_left(t_philo *philo)
{
	int	left;

	left = (philo->id - 1);
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_lock(&philo->data->forks[left]);
		print_philo(philo, "has taken a fork");
		pthread_mutex_unlock(&philo->data->forks[left]);
		return (1);
	}
	return (0);
}

int	take_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = (philo->id - 1);
	right = (philo->id) % philo->data->nb_philo;
	if (take_fork_order(philo) == 1)
		return (1);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[left]);
		print_philo(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[right]);
		print_philo(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[right]);
		print_philo(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[left]);
		print_philo(philo, "has taken a fork");
	}
	return (0);
}

void	let_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = (philo->id - 1);
	right = (philo->id) % philo->data->nb_philo;
	pthread_mutex_unlock(&philo->data->forks[left]);
	pthread_mutex_unlock(&philo->data->forks[right]);
}

void	philo_eat(t_philo *philo)
{
	if (take_forks(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->death_mutex);
	print_philo(philo, "is eating");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_usleep(philo->data->time_to_eat, philo->data);
	let_forks(philo);
}
