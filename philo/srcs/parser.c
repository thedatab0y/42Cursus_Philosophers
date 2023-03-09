/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:14:21 by busmanov          #+#    #+#             */
/*   Updated: 2023/03/09 17:35:50 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//used to check whether the command line args are valid numbers.
int	check_if_number(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_isnumber(argv[i]))
		{
			printf(RED"Error\n\"%s\" is not a number\n"DISCOLOR, argv[i]);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

// used to validate the values of command line arguvemnts passed
//param is being used to store the value of specific command like
//argv passed to the program. a parameter that program
// expects to recieve as a command like argv like die, time to eat...
int	is_valid_argv(int index, int param)
{
	if (index == 0 && !param)
		printf(RED"Error\nThere must be at least 1 philosopher\n"DISCOLOR);
	else if (index >= 0 && index < 5 && param < 0)
		printf(RED"Error\nThe argument cannot be negative\n"DISCOLOR);
	else
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

// used to convert CLA passed from strings to int and validate
// the resulting int array 'param' can then be used as input for other functions
int	*atoi_array(int argc, char **argv)
{
	int	i;
	int	*param;

	i = 0;
	if (check_if_number(argv))
		return (NULL);
	param = malloc(sizeof(int) * MAXARGC);
	if (!param)
		return (NULL);
	while (argv[i])
	{
		param[i] = ft_atoi(argv[i]);
		if (is_valid_argv(i, param[i]))
			return (NULL);
		i++;
	}
	if (argc == 5)
		param[num_of_meals] = DEFAULT;
	return (param);
}

// parse and validate the command line args and to allocate memory
// for and initialize an int array that represents parsed arguments.
// the resulting int array can then be used as input for other functions.
int	*parse(int argc, char **argv)
{
	int		*param;

	if (argc < 5 | argc > 6)
	{
		printf("Invalid number of arguments.\n");
		return (NULL);
	}
	param = atoi_array(argc, argv + 1);
	if (!param)
		return (free_mem(NULL, NULL, param));
	return (param);
}
