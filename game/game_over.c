/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:59:29 by drhaouha          #+#    #+#             */
/*   Updated: 2024/08/02 08:22:14 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	to_argb(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

void	apply_grayscale(t_img *img)
{
	t_pt	pos;
	int		color;
	int		gray;
	int		rgb[3];
	int		index;

	pos.y = -1;
	while (++pos.y < img->height)
	{
		pos.x = -1;
		while (++pos.x < img->width)
		{
			color = get_pixel_from_image(img, (t_pt){pos.x, pos.y});
			index = (pos.x * img->bpp / 8) + (pos.y * img->size_line);
			rgb[0] = (color >> 16) & 0xFF;
			rgb[1] = (color >> 8) & 0xFF;
			rgb[2] = color & 0xFF;
			gray = (rgb[0] + rgb[1] + rgb[2]) / 3;
			*(unsigned int *)(img->data + index)
				= to_argb(0, gray, gray, gray);
		}
	}
}

void	game_is_over(t_slng *so)
{
	int		i;

	so->game_over->x = (so->width - so->game_over->width) / 2;
	so->game_over->y = (so->height - so->game_over->height) / 2;
	so->finished = true;
	i = 40;
	while (i-- > 0)
	{
		__timer(8000000);
		apply_grayscale(so->ground_tmp->img);
		insert_image_to(so->ground_tmp->img, so->game_over,
			(t_pt){so->game_over->x - so->ground_tmp->img->x,
			so->game_over->y - so->ground_tmp->img->y});
		draw_frame(so);
	}
	exit_game(so);
}
