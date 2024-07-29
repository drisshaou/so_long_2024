/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_player_in_window.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:51:25 by drhaouha          #+#    #+#             */
/*   Updated: 2024/07/29 08:57:45 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	displace_playground_n_player(t_slng *so, t_pt delta)
{
	static int	frame_count = 0;

	if (++frame_count < 2000000)
		return ;
	frame_count = 0;
	if ((so->playground->img->width + so->playground->img->x) >= so->width
		&& so->player->img->x > (so->width / 2))
	{
		so->playground->img->x -= delta.x;
		so->player->img->x -= delta.x;
		so->ghost->img->x -= delta.x;
	}
	if ((so->playground->img->height + so->playground->img->y) >= so->height
		&& so->player->img->y > (so->height / 2))
	{
		so->playground->img->y -= delta.y;
		so->player->img->y -= delta.y;
		so->ghost->img->y -= delta.y;
	}
	so->playground_tmp->img->x = so->playground->img->x;
	so->playground_tmp->img->y = so->playground->img->y;
	mlx_put_image_to_window(so->mlx, so->win, so->playground_tmp->img->ptr,
		so->playground_tmp->img->x, so->playground_tmp->img->y);
}

t_pt	prevent_zero_div(t_slng *so, t_pt p)
{
	p.x = so->playground->img->x - p.x;
	p.y = so->playground->img->y - p.y;
	p.x += (p.x == 0);
	p.y += (p.y == 0);
	return (p);
}

t_pt	get_displacement(t_slng *so)
{
	t_pt	playground;
	t_pt	player;

	playground = (t_pt){so->playground->img->x, so->playground->img->y};
	player = (t_pt){so->player->img->x, so->player->img->y};
	while (((so->playground->img->width + playground.x) >= so->width
			&& player.x > (so->width / 2)) || (player.y > (so->height / 2)
			&& (so->playground->img->height + playground.y) >= so->height))
	{
		if (player.x > (so->width / 2)
			&& (so->playground->img->width + playground.x) >= so->width)
		{
			playground.x -= 1;
			player.x -= 1;
		}
		if (player.y > (so->height / 2)
			&& (so->playground->img->height + playground.y) >= so->height)
		{
			playground.y -= 1;
			player.y -= 1;
		}
	}
	return (prevent_zero_div(so, playground));
}

void	center_player_in_window(t_slng *so)
{
	t_pt	playground_diff;
	t_pt	delta;
	t_img	layer;

	if ((so->player->img->x - so->player->img->width) > so->width
		|| (so->player->img->y - so->player->img->height) > so->height)
	{
		playground_diff = get_displacement(so);
		layer = get_exit_layer(so, so->playground_full->img);
		insert_layer_in_image(so, so->playground_tmp->img, layer);
		delta = (t_pt){playground_diff.x / playground_diff.y, 1};
		if (playground_diff.y > playground_diff.x)
			delta = (t_pt){1, playground_diff.y / playground_diff.x};
		while ((so->player->img->x > (so->width / 2)
				&& (so->playground->img->width
					+ so->playground->img->x) >= so->width)
			|| (so->player->img->y > (so->height / 2)
				&& (so->playground->img->height
					+ so->playground->img->y) >= so->height))
			displace_playground_n_player(so, delta);
		insert_image_to(so->playground_tmp->img,
			so->playground_full->img, (t_pt){0, 0});
		so->player->img->y += (-so->playground->img->y % 24);
		so->ghost->img->y += (-so->playground->img->y % 24);
	}
}
