/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:02:34 by drhaouha          #+#    #+#             */
/*   Updated: 2024/08/02 09:12:09 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_img	*get_ground_layer(t_slng *so)
{
	t_img	*ground_layer;
	t_pt	p;

	p = coord_to_position(so,
			(t_coord){so->player->col, so->player->row}, *so->map_dim);
	ground_layer = so->ground_full->img;
	if (p.x == so->player->img->x && p.y == so->player->img->y)
		ground_layer = so->ground->img;
	return (ground_layer);
}

void	clean_frame(t_slng *so)
{
	t_img	layer;

	layer = get_background_layer(so, get_ground_layer(so),
			(t_pt){so->player->img->_x, so->player->img->_y},
			(t_size){so->player->img->width, so->player->img->height});
	insert_layer_in_image(so, so->ground_tmp->img, layer);
	layer = get_background_layer(so, get_ground_layer(so),
			(t_pt){so->player->img->x, so->player->img->y},
			(t_size){so->player->img->width, so->player->img->height});
	insert_layer_in_image(so, so->ground_full->img, layer);
	if (so->has_ghost)
	{
		layer = get_background_layer(so, so->ground_full->img,
				(t_pt){so->ghost->img->_x, so->ghost->img->_y},
				(t_size){so->ghost->img->width, so->ghost->img->height});
		insert_layer_in_image(so, so->ground_tmp->img, layer);
	}
	layer = get_background_layer(so, so->ground_full->img,
			(t_pt){(so->width - 164) / 2, 2},
			(t_size){164, 20});
	insert_layer_in_image(so, so->ground_tmp->img, layer);
	layer = get_background_layer(so, so->ground_full->img,
			(t_pt){4 - 4, so->height - 24 - 4},
			(t_size){(so->collectibes * 24) + (so->collectibes * 2) + 8, 32});
	insert_layer_in_image(so, so->ground_tmp->img, layer);
}

void	update_grounds_pos(t_slng *so)
{
	so->ground_full->img->x = so->ground->img->x;
	so->ground_full->img->y = so->ground->img->y;
	so->ground_tmp->img->x = so->ground->img->x;
	so->ground_tmp->img->y = so->ground->img->y;
}

int	draw_frame(t_slng *so)
{
	static int	count = 0;
	int			id;

	update_grounds_pos(so);
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
	mlx_put_image_to_window(so->mlx, so->win, so->ground_tmp->img->ptr,
		so->ground_tmp->img->x, so->ground_tmp->img->y);
	count = update_player_frame(so, count);
	return (0);
}
