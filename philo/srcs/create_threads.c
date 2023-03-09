/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:13:57 by busmanov          #+#    #+#             */
/*   Updated: 2023/03/09 06:15:27 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_philo(t_philo *philo, int num_of_philos, pthread_t *waiter)
{
	int			i;
	pthread_t	*philo_thread;

	i = 0;
	philo_thread = malloc(sizeof(pthread_t) * num_of_philos);
	if (!philo_thread)
		return (EXIT_FAILURE);
	while (i < num_of_philos)
	{
		if (pthread_create(
				&philo_thread[i], NULL, &simulation, (void *)(philo + i)))
			return (EXIT_FAILURE);
		i++;
	}
	if (pthread_join(*waiter, NULL))
		return (EXIT_FAILURE);
	while (i--)
		if (pthread_join(philo_thread[i], NULL))
			return (EXIT_FAILURE);
	free(philo_thread);
	return (EXIT_SUCCESS);
}

int	create_threads(t_philo *philo, pthread_mutex_t	*fork)
{
	pthread_t	waiter;

	if (pthread_create(&waiter, NULL, &waiter_routine, (void *)philo))
		return (EXIT_FAILURE);
	if (create_philo(philo, philo->param[num_of_philo], &waiter))
		return (EXIT_FAILURE);
	if (pthread_mutex_destroy(fork))
		return (EXIT_FAILURE);
	if (pthread_mutex_destroy(philo->print))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
