/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:02:49 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/18 11:14:21 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_overflow(long result, int sign)
{
	if ((sign == 1 && result > INT_MAX) || (sign == -1 && - result < INT_MIN))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (ft_overflow(result, sign))
			return (-1);
		i++;
	}
	return ((int)(result * sign));
}

int	is_dead(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->death_mutex);
	dead = data->someone_died;
	pthread_mutex_unlock(&data->death_mutex);
	return (dead);
}

void	set_death(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->death_mutex);
}

int	check_death(t_philo *philo)
{
	long	current_time;
	long	time_to_live;
	long	last_meal;

	current_time = get_time();
	pthread_mutex_lock(&philo->data->death_mutex);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->data->death_mutex);
	time_to_live = current_time - last_meal;
	if (time_to_live > philo->data->time_to_die)
		return (1);
	return (0);
}
