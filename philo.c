/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:29:47 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/15 17:46:59 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	philo;
	int	i;

	i = 0;
	if (ac < 2)
		return (ft_error("Invalid argument\n", 2), 2);
	while (i < ft_atoi(av[1]))
	{
		create_thread(philo.id, &philo);
		i++;
	}
	(void)philo;
	(void)av;
	return (0);
}
