/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:14:34 by busmanov          #+#    #+#             */
/*   Updated: 2023/03/09 17:36:03 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// the loop goes on till philo has eaten
// the total num of meals specified in the program
// philo->num_of_meals = num of meals it has currently eaten
// philo-> param[num_of_meals] = total num of meals it needs to eat
// The tid parameter is cast to a pointer to 
// a t_philo struct and assigned to the variable philo
// inside while, if the time since the philo's last meal is greater
// than the time allowed for the philo to die, it prints
// msg that the philo died
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

// prints what the philo is doing
// if (action == eating), last_meal time to current_time
// that will be later used to check if a philo has
// exceeded the allowed time without a meal and thus die
// increments the num_meals by 1, coz it has just eaten
// ft_usleep to make philo sleep for specified time
// time_to_eat represents the time the philo spends eatin
void	action(t_philo *philo, t_lifecycle action)
{
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

// main logic for each philo's behaviour is implemented
// casts 'tid' to a 't_philo' and assign to 'philo'
// that allows the func to access the philo's info like
// 'id', 'num_of_meals', 'left_fork' and param
// if philo's ID is even, philo sleeps
// ' even num-numbered philos do not try to grap their right fork
// before left fork, which would cause a deadlock.
// - the loop runs as long as the philo has not reached its required num
// of meals and is still alive and there are more than 1 philo.
// - locks the philo's left fork and then the right fork to
// prevent others trying to grap the same forks at the same time
// action() updates philos state and prints
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
