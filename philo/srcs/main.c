/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:14:14 by busmanov          #+#    #+#             */
/*   Updated: 2023/03/09 06:15:17 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
