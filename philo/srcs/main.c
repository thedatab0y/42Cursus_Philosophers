/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:14:14 by busmanov          #+#    #+#             */
/*   Updated: 2023/03/09 17:20:34 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// return value of parse is stored in the param variable
// the INITIALIZE func is used for setting up the program's data structures
// and initialize any necessary resources like mutexes and threads
// job: parse and validate CLA, initialize data structs, 
// then execute the main logic.
int	main(int argc, char **argv)
{
	int		*param;

	param = parse(argc, argv);
	if (!param)
		return (EXIT_FAILURE);
	if (!initialize(param))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
