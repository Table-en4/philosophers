/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:50:56 by molapoug          #+#    #+#             */
/*   Updated: 2025/07/01 15:57:45 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*threads_1(void *args)
{
	printf("t'es dans le threads idiot\n");

	pthread_exit(EXIT_SUCCESS);
}

int	main(void)
{
	pthread_t	thread1;

	printf("étape avant la création du thread\n");

	pthread_create(&thread1, NULL, threads_1, NULL);
	printf("apres la creation du thread\n");
	return (EXIT_SUCCESS);
}
