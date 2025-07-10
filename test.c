/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:50:56 by molapoug          #+#    #+#             */
/*   Updated: 2025/07/10 14:16:08 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*thread_routine(void *arg)
{
	/*t_philo	id;

	id.id = 0;*/
	(void)arg;
	static int i = 0;
	printf("je cré un thread %i\n", i++);
	return NULL;
}
