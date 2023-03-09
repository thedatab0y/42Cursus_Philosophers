/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:14:05 by busmanov          #+#    #+#             */
/*   Updated: 2023/03/09 06:15:31 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
