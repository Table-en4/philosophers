/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:29:47 by molapoug          #+#    #+#             */
/*   Updated: 2025/07/03 19:09:14 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_thread(int ac, t_philo *philo)
{
	int	i;
	
	i = 0;
	while (i <= (ac - 1))
	{
		pthread_create(philo->philo, NULL threads_1, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo	philo;

	if (ac != 2)
		ft_error_fd("Invalid argument\n", 2);
	
	(void)av;
}
