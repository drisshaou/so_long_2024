/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:02:34 by drhaouha          #+#    #+#             */
/*   Updated: 2024/08/02 08:22:14 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_img	get_collected_layer(t_slng *so, t_img *img)
{
	int		i;
	t_img	layer;
	t_pt	pos;

	layer.x = 4;
	layer.y = so->height - 24 - 4;
	layer.width = (so->collectibes * 24) + (so->collectibes * 2);
	layer.height = 24;
	layer.ptr = mlx_new_image(so->mlx, layer.width, layer.height);
	layer.data = mlx_get_data_addr(layer.ptr,
			&layer.bpp, &layer.size_line, &layer.endian);
	ground_to_layer(&layer, img);
	i = 0;
	while (i < so->collectibes)
	{
		pos = (t_pt){(i * 24) + (i * 2), 0};
		if (i < so->player->collected)
			insert_image_to(&layer, so->cherry_fg, pos);
		else
			insert_image_to(&layer, so->cherry_bg, pos);
		i++;
	}
	return (layer);
}

t_img	get_counter_layer(t_slng *so, t_img *img, int nb)
{
	int		i;
	t_img	layer;
	t_pt	pos;

	i = 10;
	layer.x = (so->width - (i * 16)) / 2;
	layer.y = 4;
	layer.width = (i * 16);
	layer.height = 16;
	layer.ptr = mlx_new_image(so->mlx, layer.width, layer.height);
	layer.data = mlx_get_data_addr(layer.ptr,
			&layer.bpp, &layer.size_line, &layer.endian);
	ground_to_layer(&layer, img);
	while (i > 0)
	{
		pos = (t_pt){(i - 1) * 16, 0};
		so->numeric->img->ptr = so->numeric->ptrs[nb % 10];
		so->numeric->img->data = mlx_get_data_addr(so->numeric->img->ptr,
				&so->numeric->img->bpp, &so->numeric->img->size_line,
				&so->numeric->img->endian);
		insert_image_to(&layer, so->numeric->img, pos);
		nb /= 10;
		i--;
	}
	return (layer);
}

t_img	get_ghost_layer(t_slng *so, t_img *img)
{
	t_img	layer;

	layer.x = so->ghost->img->x;
	layer.y = so->ghost->img->y;
	layer.width = so->ghost->img->width;
	layer.height = so->ghost->img->height;
	layer.ptr = mlx_new_image(so->mlx, layer.width, layer.height);
	layer.data = mlx_get_data_addr(layer.ptr,
			&layer.bpp, &layer.size_line, &layer.endian);
	ground_to_layer(&layer, img);
	insert_image_to(&layer, so->ghost->img, (t_pt){0, 0});
	return (layer);
}

t_img	get_player_layer(t_slng *so, t_img *img)
{
	t_img	layer;

	layer.x = so->player->img->x;
	layer.y = so->player->img->y;
	layer.width = so->player->img->width;
	layer.height = so->player->img->height;
	layer.ptr = mlx_new_image(so->mlx, layer.width, layer.height);
	layer.data = mlx_get_data_addr(layer.ptr,
			&layer.bpp, &layer.size_line, &layer.endian);
	ground_to_layer(&layer, img);
	insert_image_to(&layer, so->player->img, (t_pt){0, 0});
	return (layer);
}

t_img	get_exit_layer(t_slng *so, t_img *img)
{
	int		i;
	t_img	layer;
	t_pt	pos;
	int		gap;

	gap = (12 * so->map_dim->rows) / 40;
	i = so->exit->row;
	layer.x = so->ground->img->x + (gap * 40) + (-12 * so->exit->row)
		+ (so->exit->col * 40);
	layer.y = so->ground->img->y;
	layer.width = 40;
	layer.height = 24 * i;
	layer.ptr = mlx_new_image(so->mlx, layer.width, layer.height);
	layer.data = mlx_get_data_addr(layer.ptr,
			&layer.bpp, &layer.size_line, &layer.endian);
	ground_to_layer(&layer, img);
	while (i > 0)
	{
		pos = (t_pt){0, (i - 1) * 24};
		so->ladder->data = mlx_get_data_addr(so->ladder->ptr,
				&so->ladder->bpp, &so->ladder->size_line, &so->ladder->endian);
		insert_image_to(&layer, so->ladder, pos);
		i--;
	}
	return (layer);
}
