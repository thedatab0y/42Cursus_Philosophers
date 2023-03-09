/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:14:27 by busmanov          #+#    #+#             */
/*   Updated: 2023/03/09 06:19:23 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print(t_philo *philo, t_lifecycle action)
{
	long	timestamp;

	pthread_mutex_lock(philo->print);
	timestamp = current_time() - philo->start_time;
	if (*philo->alive_or_dead
		|| philo->num_of_meals == philo->param[num_of_meals])
	{
		pthread_mutex_unlock(philo->print);
		return ;
	}
	else if (action == take_forks)
	{
		printf(GREEN"%ld %d has taken a fork\n"DISCOLOR, timestamp, philo->id);
		printf(GREEN"%ld %d has taken a fork\n"DISCOLOR, timestamp, philo->id);
	}
	else if (action == eating)
		printf(YELLOW"%ld %d is eating\n"DISCOLOR, timestamp, philo->id);
	else if (action == sleeping)
		printf(BLUE"%ld %d is sleeping\n"DISCOLOR, timestamp, philo->id);
	else if (action == thinking)
		printf(MAGENTA"%ld %d is thinking\n"DISCOLOR, timestamp, philo->id);
	else if (action == died)
		printf(RED"%ld %d died\n"DISCOLOR, timestamp, philo->id);
	pthread_mutex_unlock(philo->print);
}
