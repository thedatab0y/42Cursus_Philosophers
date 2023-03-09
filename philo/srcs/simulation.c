/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:14:34 by busmanov          #+#    #+#             */
/*   Updated: 2023/03/09 06:15:45 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*waiter_routine(void *tid)
{
	t_philo	*philo;

	philo = ((t_philo *)tid);
	while (philo->num_of_meals != philo->param[num_of_meals])
	{
		if (current_time() - philo->last_meal_time > philo->param[time_to_die])
		{
			print(philo, died);
			*philo->alive_or_dead = DEAD;
			return (NULL);
		}
	}
	return (NULL);
}

void	action(t_philo *philo, t_lifecycle action)
{
	//int	timestamp;

	//timestamp = current_time() - philo->start_time;
	print(philo, action);
	if (action == eating)
	{
		philo->last_meal_time = current_time();
		philo->num_of_meals++;
		ft_usleep(philo->param[time_to_eat], philo);
	}
	else if (action == sleeping)
		ft_usleep(philo->param[time_to_sleep], philo);
}

void	*simulation(void *tid)
{
	t_philo	*philo;

	philo = ((t_philo *)tid);
	if (!(philo->id % 2))
		ft_usleep(philo->param[time_to_eat], philo);
	while (philo->num_of_meals != philo->param[num_of_meals]
		&& !(*philo->alive_or_dead) && philo->param[num_of_philo] != 1)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		action(philo, take_forks);
		action(philo, eating);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		action(philo, sleeping);
		action(philo, thinking);
	}
	return (NULL);
}
