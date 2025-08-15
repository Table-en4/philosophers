/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:31:02 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/15 17:44:59 by molapoug         ###   ########.fr       */
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
	while (tid->id)
		tid->id++;
	return (tid->id);
}

void *thread_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    pthread_mutex_lock(&philo->data->count_mutex);
    printf("Philo %d mange\n", philo->id);
    pthread_mutex_unlock(&philo->data->count_mutex);
    return NULL;
}

int create_thread(t_data *data, t_philo *philos)
{
    int	i;
	
	i = 0;
    while (i < data->nb_philo)
    {
        pthread_create(&philos[i].thread, NULL, thread_routine, &philos[i]);
        i++;
    }
    i = 0;
    while (i < data->nb_philo)
        pthread_join(philos[i++].thread, NULL);
    return 0;
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
