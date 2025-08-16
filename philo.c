/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:29:47 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/16 14:06:46 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, char **av)
{
	int	i;

	i = 0;
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (ft_error("Erreur de malloc dans les forks", 2), free(data->forks), 2);
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	if (av[5])
		data->nb_meals = ft_atoi(av[5]);
	else
		data->nb_meals = -1;
	data->someone_died = 0;
	data->start_time = get_time();
	if (pthread_mutex_init(&data->count_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;
	int	i;

	if (ac < 5 || ac > 6)
		return (ft_error("Invalid arguments\n", 2), 2);
	if (init_data(&data, av) != 0)
		return (ft_error("Failed to init data\n", 2), 2);
	philos = malloc(sizeof(t_philo) * data.nb_philo);
	if (!philos)
		return (ft_error("Malloc failed\n", 2), 2);
	if (create_thread(&data, philos) != 0)
	{
		free(philos);
		return (2);
	}
	pthread_mutex_destroy(&data.print_mutex);
	i = 0;
	while (i < data.nb_philo)
    	pthread_mutex_destroy(&data.forks[i++]);
	free(data.forks);
	return (0);
}
