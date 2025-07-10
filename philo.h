/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:50:39 by molapoug          #+#    #+#             */
/*   Updated: 2025/07/10 14:14:50 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_philo {
    int	id;
    int	meals_eaten;
    long	last_meal_time;
    pthread_t	*thread;
    struct s_data	*data;
} t_philo;

typedef struct s_data {
    int	nb_philo;
    int	time_to_die;
    int	time_to_eat;
    int	time_to_sleep;
    int	nb_meals;
    int	someone_died;
    long	start_time;
    pthread_mutex_t	*forks;
    pthread_mutex_t	print_mutex;
    pthread_mutex_t	death_mutex;
} t_data;


/* ######################### */
/* fonction to get the error */
/* ######################### */
void	ft_error(char *str, int fd);

/* ######################### */
/*  fonction to get thrrads  */
/* ######################### */
int	create_thread(int ac, t_philo *philo);
void	*thread_routine(void *arg);
void	*threads_1();

#endif
