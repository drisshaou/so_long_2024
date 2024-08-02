/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:09:17 by drhaouha          #+#    #+#             */
/*   Updated: 2024/08/02 08:22:14 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_ghost(t_slng *so)
{
	if (so->ghost->img != NULL)
		free(so->ghost->img);
	if (so->ghost != NULL)
		free(so->ghost);
}

void	free_numeric(t_slng *so)
{
	if (so->numeric->img != NULL)
		free(so->numeric->img);
	if (so->numeric != NULL)
		free(so->numeric);
}

void	free_ground_images(t_slng *so)
{
	if (so->ladder != NULL)
		free(so->ladder);
	if (so->point != NULL)
		free(so->point);
	if (so->cherry != NULL)
		free(so->cherry);
	if (so->cherry_fg != NULL)
		free(so->cherry_fg);
	if (so->cherry_bg != NULL)
		free(so->cherry_bg);
	if (so->floor != NULL)
		free(so->floor);
	if (so->grey_cube != NULL)
		free(so->grey_cube);
	if (so->blue_cube != NULL)
		free(so->blue_cube);
	if (so->game_over != NULL)
		free(so->game_over);
	if (so->you_win != NULL)
		free(so->you_win);
}

bool	progressive_free(t_slng *so, int i)
{
	if (i == 8)
		free_ground_images(so);
	if (i >= 7)
		free_numeric(so);
	if (i >= 6)
		free_ghost(so);
	if (i >= 5)
		free_player(so);
	if (i >= 4)
		free_grounds(so);
	if (i >= 3)
		free_collect(&so->collect, *so->map_dim);
	if (i >= 2)
		free(so->exit);
	if (i >= 1)
	{
		free_map(&so->map);
		free(so->map_dim);
	}
	return (false);
}

void	free_slng(t_slng *so, int i)
{
	progressive_free(so, i);
	free(so->mlx);
	free(so);
}
