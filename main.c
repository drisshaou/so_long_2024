/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:23:59 by drhaouha          #+#    #+#             */
/*   Updated: 2024/07/29 15:03:59 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	char	**map;

	map = NULL;
	if (ac == 2)
	{
		if (!parse_file(&map, av[1]))
			return (0);
		else
			try_game(&map);
	}
	return (1);
}
