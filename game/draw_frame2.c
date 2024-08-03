/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:02:34 by drhaouha          #+#    #+#             */
/*   Updated: 2024/08/03 20:43:54 by drhaouha         ###   ########.fr       */
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

void	insert_ghost_layer(t_slng *so)
{
	t_img	layer;

	layer = get_ghost_layer(so, so->ground_tmp->img);
	insert_layer_in_image(so, so->ground_tmp->img, layer);
}

void	refresh_frame(t_slng *so)
{
	t_img	layer;

	if (so->finished == 0)
	{
		layer = get_player_layer(so, so->ground_tmp->img);
		insert_layer_in_image(so, so->ground_tmp->img, layer);
	}
	if (so->has_ghost)
		insert_ghost_layer(so);
	layer = get_exit_layer(so, so->ground_tmp->img);
	insert_layer_in_image(so, so->ground_tmp->img, layer);
	if (so->finished != 0)
	{
		layer = get_player_layer(so, so->ground_tmp->img);
		insert_layer_in_image(so, so->ground_tmp->img, layer);
		if (so->has_ghost && so->finished == 1)
			insert_ghost_layer(so);
	}
	layer = get_counter_layer(so, so->ground_tmp->img,
			so->player->counter);
	insert_layer_in_image(so, so->ground_tmp->img, layer);
	layer = get_collected_layer(so, so->ground_tmp->img);
	insert_layer_in_image(so, so->ground_tmp->img, layer);
}

t_pt	coord_to_position(t_slng *so, t_coord dest, t_dim d)
{
	t_coord	cur;
	int		gap;
	t_pt	pos;

	pos = (t_pt){0, 0};
	d.cols = ((12 * d.rows) + (d.cols * 40)) / 40;
	gap = ((12 * d.rows) / 40);
	cur.row = 0;
	while (cur.row < d.rows)
	{
		cur.col = 0;
		while (cur.col < d.cols)
		{
			pos = (t_pt){(-12 * cur.row) + (cur.col * 40), cur.row * 24};
			if (cur.col >= gap
				&& (cur.col - gap) == dest.col && cur.row == dest.row)
				return ((t_pt){pos.x + so->ground->img->x,
					pos.y + so->ground->img->y});
			cur.col++;
		}
		cur.row++;
	}
	return (pos);
}
