/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:48:33 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/16 14:03:41 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.c"

void	print_philo(t_philo *philo, char *msg)
{
	long	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->someone_died)
	{
		time = get_time() - philo->data->start_time;
		printf("%ld%d%s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	take_forks(t_philo *philo)
{
	int	left;
	int right;

	left = philo->id - 1;
	right = philo->id % philo->data->nb_philo;
	if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->data->forks[left_fork]);
        safe_print(philo, "has taken a fork");
        pthread_mutex_lock(&philo->data->forks[right_fork]);
        safe_print(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&philo->data->forks[right_fork]);
        safe_print(philo, "has taken a fork");
        pthread_mutex_lock(&philo->data->forks[left_fork]);
        safe_print(philo, "has taken a fork");
    }
    return (0);
}

void let_forks(t_philo *philo)
{
    int left_fork = philo->id - 1;
    int right_fork = philo->id % philo->data->nb_philo;

    pthread_mutex_unlock(&philo->data->forks[left_fork]);
    pthread_mutex_unlock(&philo->data->forks[right_fork]);
}

void philo_eat(t_philo *philo)
{
    take_forks(philo);

    print_philo(philo, "is eating");
    philo->last_meal_time = get_time();
    philo->meals_eaten++;

    usleep(philo->data->time_to_eat * 1000);

    let_forks(philo);
}
