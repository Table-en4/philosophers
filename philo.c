/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:29:47 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/17 21:08:59 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->count_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return (1);
	return (0);
}

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
		return (ft_error("Erreur de malloc dans les forks\n", 2), 2);
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
	if (init_mutex(data) == 1)
		return (1);
	return (0);
}

void	cleanup_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->count_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data->forks);
}

int	check_args(int ac, char **av)
{
    long    val;
    int     i;

    if (ac < 5 || ac > 6)
        return (ft_error("Invalid arguments\n", 2), 2);
    i = 1;
    while (i < ac)
    {
        if (!ft_is_digit(av[i]))
            return (ft_error("Letter in the argument\n", 2), 2);
        val = ft_atoi(av[i]);
        if (val <= 0)
            return (ft_error("Number lower than 0\n", 2), 2);
        i++;
    }
    val = ft_atoi(av[1]);
    if (val > 200)
        return (ft_error("Number bigger than 200\n", 2), 2);
    return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		*philos;
	pthread_t	monitor;

	if (check_args(ac, av))
		return (2);
	if (init_data(&data, av) != 0)
		return (ft_error("Failed to init data\n", 2), 2);
	philos = malloc(sizeof(t_philo) * data.nb_philo);
	if (!philos)
		return (ft_error("Malloc failed\n", 2), cleanup_data(&data), 2);
	if (create_thread(&data, philos, &monitor) != 0)
		return (free(philos), cleanup_data(&data), 2);
	pthread_join(monitor, NULL);
	join_all_threads(philos, data.nb_philo);
	return (free(philos), cleanup_data(&data), 0);
}