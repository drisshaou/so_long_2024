/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:02:34 by drhaouha          #+#    #+#             */
/*   Updated: 2024/07/29 08:26:18 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	insert_image_to(t_img *dest, t_img *src, t_pt dst)
{
	t_pt	pos;
	int		color;

	pos.y = -1;
	while (++pos.y < src->height)
	{
		pos.x = -1;
		while (++pos.x < src->width)
		{
			color = get_pixel_from_image(src, (t_pt){pos.x, pos.y});
			if (color == ALPHA)
				color = get_pixel_from_image(dest, (t_pt){
						dst.x + pos.x, dst.y + pos.y});
			put_pixel_to_image(dest, (t_pt){
				dst.x + pos.x, dst.y + pos.y}, color);
		}
	}
}

void	insert_layer_in_image(t_slng *so, t_img *img, t_img layer)
{
	insert_image_to(img, &layer, (t_pt){layer.x - img->x, layer.y - img->y});
	mlx_destroy_image(so->mlx, layer.ptr);
}

void	refresh_frame(t_slng *so)
{
	t_img	layer;

	if (so->finished)
	{
		layer = get_exit_layer(so, so->playground_full->img);
		insert_layer_in_image(so, so->playground_tmp->img, layer);
		layer = get_player_layer(so, so->playground_tmp->img);
	}
	else
		layer = get_player_layer(so, so->playground->img);
	insert_layer_in_image(so, so->playground_tmp->img, layer);
	if (so->has_ghost)
	{
		layer = get_ghost_layer(so, so->playground_tmp->img);
		insert_layer_in_image(so, so->playground_tmp->img, layer);
	}
	if (!so->finished)
		layer = get_exit_layer(so, so->playground_tmp->img);
	if (!so->finished)
		insert_layer_in_image(so, so->playground_tmp->img, layer);
	layer = get_counter_layer(so, so->playground_tmp->img,
			so->player->counter);
	insert_layer_in_image(so, so->playground_tmp->img, layer);
	layer = get_collected_layer(so, so->playground_tmp->img);
	insert_layer_in_image(so, so->playground_tmp->img, layer);
}

void	clean_frame(t_slng *so)
{
	t_img	layer;

	layer = get_background_layer(so, so->playground->img,
			(t_pt){so->player->img->_x, so->player->img->_y},
			(t_size){so->player->img->width, so->player->img->height});
	insert_layer_in_image(so, so->playground_tmp->img, layer);
	layer = get_background_layer(so, so->playground->img,
			(t_pt){so->player->img->_x, so->player->img->_y},
			(t_size){so->player->img->width, so->player->img->height});
	insert_layer_in_image(so, so->playground_full->img, layer);
	if (so->has_ghost)
	{
		layer = get_background_layer(so, so->playground_full->img,
				(t_pt){so->ghost->img->_x, so->ghost->img->_y},
				(t_size){so->ghost->img->width, so->ghost->img->height});
		insert_layer_in_image(so, so->playground_tmp->img, layer);
	}
	layer = get_background_layer(so, so->playground_full->img,
			(t_pt){(so->width - 164) / 2, 2},
			(t_size){164, 20});
	insert_layer_in_image(so, so->playground_tmp->img, layer);
	layer = get_background_layer(so, so->playground_full->img,
			(t_pt){4 - 4, so->height - 24 - 4},
			(t_size){(so->collectibes * 24) + (so->collectibes * 2) + 8, 32});
	insert_layer_in_image(so, so->playground_tmp->img, layer);
}

void	update_playgrounds_pos(t_slng *so)
{
	so->playground_full->img->x = so->playground->img->x;
	so->playground_full->img->y = so->playground->img->y;
	so->playground_tmp->img->x = so->playground->img->x;
	so->playground_tmp->img->y = so->playground->img->y;
}
