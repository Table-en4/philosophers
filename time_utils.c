/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:16:11 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/18 11:16:43 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_philos(t_philo *philos, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_destroy(&philos[i].meal_mutex);
		i++;
	}
}

int	ft_is_digit(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	time_diff(long start, long end)
{
	return (end - start);
}

void	ft_usleep(long time_ms, t_data *data)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time();
	elapsed = get_time();
	while ((elapsed - start) < time_ms)
	{
		elapsed = get_time();
		if (is_dead(data))
			break ;
		remaining = time_ms - elapsed;
		if (remaining > 10)
			usleep(1000);
		else if (remaining > 1)
			usleep(100);
		else
			usleep(10);
	}
}
