/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:02:34 by drhaouha          #+#    #+#             */
/*   Updated: 2024/07/29 08:16:44 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	draw_frame(t_slng *so)
{
	static int	count = 0;
	int			id;

	update_playgrounds_pos(so);
	id = (so->player->frame % 6)
		* (so->player->left || so->player->right
			|| so->player->up || so->player->down);
	so->player->img->ptr = so->player->ptrs[so->player->direction][id];
	so->player->img->data = mlx_get_data_addr(so->player->img->ptr,
			&so->player->img->bpp, &so->player->img->size_line,
			&so->player->img->endian);
	if (so->has_ghost)
	{
		so->ghost->img->ptr = so->ghost->ptrs[so->ghost->direction][0];
		so->ghost->img->data = mlx_get_data_addr(so->ghost->img->ptr,
				&so->ghost->img->bpp, &so->ghost->img->size_line,
				&so->ghost->img->endian);
	}
	clean_frame(so);
	refresh_frame(so);
	mlx_put_image_to_window(so->mlx, so->win, so->playground_tmp->img->ptr,
		so->playground_tmp->img->x, so->playground_tmp->img->y);
	count = update_player_frame(so, count);
	return (0);
}
