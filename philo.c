/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:29:47 by molapoug          #+#    #+#             */
/*   Updated: 2025/07/10 14:27:26 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_thread(int ac, t_philo *philo)
{
	int	i;
	
	i = 0;
	philo->thread = malloc(sizeof(pthread_t) * ac);
	if (!philo->thread)
		return (ft_error("Malloc failde in create_thread\n", 2), 2);
	while (i < ac)
	{
		pthread_create(philo->thread, NULL, thread_routine, NULL);
		printf("thread créé : %ld\n", philo->thread[i++]);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	philo;

	if (ac < 2)
		return (ft_error("Invalid argument\n", 2), 2);
	create_thread(ac, &philo);

	(void)philo;
	(void)av;
	return (0);
}
