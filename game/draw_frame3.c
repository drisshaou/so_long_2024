/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:02:34 by drhaouha          #+#    #+#             */
/*   Updated: 2024/07/31 07:04:41 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	update_player_frame(t_slng *so, int count)
{
	so->player->frame = !(so->player->frame == 6) * so->player->frame;
	if (count % 3 == 0 && (so->player->left || so->player->right
			|| so->player->up || so->player->down))
	{
		so->player->frame++;
		count = 0;
	}
	return (++count);
}

void	playground_to_layer(t_img *layer, t_img *img)
{
	t_pt	pos;
	int		color;

	pos.y = -1;
	while (++pos.y < layer->height)
	{
		pos.x = -1;
		while (++pos.x < layer->width)
		{
			color = get_pixel_from_image(img, (t_pt){
					-img->x + layer->x + pos.x, -img->y + layer->y + pos.y});
			put_pixel_to_image(layer, pos, color);
		}
	}
}

int	get_pixel_from_image(t_img *img, t_pt pos)
{
	int	index;

	index = (pos.x * img->bpp / 8) + (pos.y * img->size_line);
	if (pos.x >= 0 && pos.x < img->width && pos.y >= 0 && pos.y < img->height)
		return (*(unsigned int *)(img->data + index));
	return (0);
}

void	put_pixel_to_image(t_img *img, t_pt pos, int color)
{
	int	index;

	index = (pos.x * img->bpp / 8) + (pos.y * img->size_line);
	if (pos.x >= 0 && pos.x < img->width && pos.y >= 0 && pos.y < img->height)
		*(unsigned int *)(img->data + index) = color;
}

t_img	get_background_layer(t_slng *so, t_img *img, t_pt p, t_size s)
{
	t_img	layer;

	layer.x = p.x;
	layer.y = p.y;
	layer.width = s.width;
	layer.height = s.height;
	layer.ptr = mlx_new_image(so->mlx, layer.width, layer.height);
	layer.data = mlx_get_data_addr(layer.ptr,
			&layer.bpp, &layer.size_line, &layer.endian);
	playground_to_layer(&layer, img);
	return (layer);
}
