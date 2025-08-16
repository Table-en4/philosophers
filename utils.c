/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:31:02 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/16 14:05:42 by molapoug         ###   ########.fr       */
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

int	philo_eat(t_philo *tid)
{
	int	i;

	i = 0;
	while (i < tid->id)
		i++;
	return (i);
}

void *thread_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    philo->last_meal_time = philo->data->start_time;
    philo->meals_eaten = 0;
    if (philo->id % 2 == 0)
        usleep(philo->data->time_to_eat * 500);
    while (!philo->data->someone_died)
    {
        philo_eat(philo);
        if (philo->data->nb_meals != -1 && philo->meals_eaten >= philo->data->nb_meals)
            break;
        print_philo(philo, "is sleeping");
        usleep(philo->data->time_to_sleep * 1000);
        print_philo(philo, "is thinking");
    }

    return NULL;
}

int create_thread(t_data *data, t_philo *philos)
{
    int i;
	
	i = 0;
    while (i < data->nb_philo)
    {
        philos[i].id = i + 1;
        philos[i].data = data;
        pthread_create(&philos[i].thread, NULL, thread_routine, &philos[i]);
        i++;
    }
    i = 0;
    while (i < data->nb_philo)
        pthread_join(philos[i++].thread, NULL);
    return 0;
}

//proteger atoi et proteger creat thread
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
