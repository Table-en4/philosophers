/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:29:47 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/15 20:06:02 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_data  data;
    t_philo *philos;

    if (ac < 2)
        return (ft_error("Invalid argument\n", 2), 2);
    data.nb_philo = ft_atoi(av[1]);
    philos = malloc(sizeof(t_philo) * data.nb_philo);
    if (!philos)
        return (ft_error("Malloc failed\n", 2), 2);
    create_thread(&data, philos);
    free(philos);
    return (0);
}
