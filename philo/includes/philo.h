/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:13:45 by busmanov          #+#    #+#             */
/*   Updated: 2023/03/08 20:13:50 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define DISCOLOR	"\x1b[0m"

# define MAXARGC	5
# define DEFAULT	-1
# define ALIVE		0
# define DEAD		1

typedef enum e_lifecycle
{
	take_forks,
	eating,
	sleeping,
	thinking,
	died
}	t_lifecycle;

typedef enum e_param
{
	num_of_philo,
	time_to_die,
	time_to_eat,
	time_to_sleep,
	num_of_meals
}	t_param;

typedef struct s_philo
{
	int				id;
	int				num_of_meals;
	long			start_time;
	long			last_meal_time;
	int				*alive_or_dead;
	int				*param;
	t_lifecycle		state;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print;
}	t_philo;

int		*parse(int argc, char **argv);
void	*waiter_routine(void *tid);
void	*simulation(void *tid);
int		create_threads(t_philo *philo, pthread_mutex_t	*fork);
void	*initialize(int *param);

long	current_time(void);
void	ft_usleep(long millisec, t_philo *philo);
void	print(t_philo *philo, t_lifecycle action);
void	*free_mem(t_philo *philo, pthread_mutex_t *fork, int *param);
int		ft_isnumber(char *str);
int		ft_atoi(const char *str);
#endif