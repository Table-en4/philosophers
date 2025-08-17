/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:16:11 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/17 17:29:23 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ft_usleep(long time, t_data *data)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (is_dead(data))
			break ;
		usleep(100);
	}
}
