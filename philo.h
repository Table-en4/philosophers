/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:50:39 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/16 14:07:19 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


/* ######################### */
/*          my color         */
/* ######################### */
#define NC "\e[0m"
#define YELLOW "\e[33m"
#define BYELLOW "\e[1;33m"
#define RED "\e[31m"
#define GREEN "\e[32m"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>


typedef struct s_philo {
    int	id;
    int	meals_eaten;
    long	last_meal_time;
    pthread_t	thread;
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
	pthread_mutex_t	count_mutex;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*print_mutex;
	unsigned int	count;
} t_data;

/* ######################### */
/* fonction to get the error */
/* ######################### */
void	ft_error(char *str, int fd);

/* ######################### */
/*  fonction to get thrrads  */
/* ######################### */
int create_thread(t_data *data, t_philo *philos);
void *thread_routine(void *arg);

int	ft_atoi(const char *str);

/* ######################### */
/*       fonction time       */
/* ######################### */
long	get_time();
long	time_diff(long start, long end);


void print_philo(t_philo *philo, char *message);
int take_forks(t_philo *philo);
void let_forks(t_philo *philo);
void philo_eat(t_philo *philo);

#endif
