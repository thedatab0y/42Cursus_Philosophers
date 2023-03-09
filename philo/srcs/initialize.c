/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:14:05 by busmanov          #+#    #+#             */
/*   Updated: 2023/03/09 17:35:45 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// initializes an array of 'num_of_philo' philo structs where
// it is a parameter passed to the program
// id = the philo's unique identifier (i + 1, indices start at 0)
// num_of_meals = num of meals the philo has eaten (0)
// start_time = the time when the philo started dining
// last_meal_time = time when the philo last ate
// alive_or_dead = initialized to 'alive_or_dead' parameter passed
// param = a pointer to the program's parameter
// left_fork = a pointer to the philo's left fork
// fork + i = fork is array of mutexes, i is philos index
// right_fork = set to ' fork _ ((i + 1) % param[num_of_philo]) where
// param[num_of_philo] is the number of philos
// i is incremented till it reaches param[num_of_philo]
t_philo	*init_philo(pthread_mutex_t *fork, pthread_mutex_t *print,
			int *param, int *alive_or_dead)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * param[num_of_philo]);
	if (!philo)
		return (NULL);
	while (i < param[num_of_philo])
	{
		philo[i].id = i + 1;
		philo[i].num_of_meals = 0;
		philo[i].start_time = current_time();
		philo[i].last_meal_time = current_time();
		philo[i].alive_or_dead = alive_or_dead;
		philo[i].param = param;
		philo[i].left_fork = fork + i;
		philo[i].right_fork = fork + ((i + 1) % param[num_of_philo]);
		philo[i].print = print;
		pthread_mutex_init(fork + i, NULL);
		i++;
	}
	return (philo);
}

// ENTRY POINT and is used for initializing the dining philo prob
// mutex is like a lock that a thread can get before accessing a shared
// resource and release when it is done using the resouce. 
// initialize  the philo structs and their attributes using the 'init_philo'
// - create seperate thread for each philo and start their activities
// using creat_threads. 
// - at last, free the memory allocated for the philo structs, fork, mutexes

void	*initialize(int *param)
{
	int				alive_or_dead;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;

	alive_or_dead = ALIVE;
	pthread_mutex_init(&print, NULL);
	fork = malloc(sizeof(pthread_mutex_t) * param[num_of_philo]);
	if (!fork)
		return (free_mem(NULL, NULL, param));
	philo = init_philo(fork, &print, param, &alive_or_dead);
	if (!philo)
		return (free_mem(NULL, fork, param));
	if (create_threads(philo, fork))
		return (free_mem(philo, fork, param));
	free_mem(philo, fork, param);
	return ((void *)EXIT_SUCCESS);
}
