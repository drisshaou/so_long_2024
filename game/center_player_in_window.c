/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_player_in_window.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:51:25 by drhaouha          #+#    #+#             */
/*   Updated: 2024/08/02 08:22:14 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	displace_ground_n_players(t_slng *so, t_pt delta)
{
	__timer(14000000);
	if ((so->ground->img->x + so->ground->img->width >= so->width + delta.x)
		&& (so->player->img->x > (so->width / 2) + so->player->img->width))
	{
		so->ground->img->x -= delta.x;
		so->player->img->x -= delta.x;
		so->ghost->img->x -= delta.x;
	}
	if ((so->ground->img->y + so->ground->img->height >= so->height + delta.y)
		&& (so->player->img->y > (so->height / 2) + so->player->img->height))
	{
		so->ground->img->y -= delta.y;
		so->player->img->y -= delta.y;
		so->ghost->img->y -= delta.y;
	}
	so->ground_tmp->img->x = so->ground->img->x;
	so->ground_tmp->img->y = so->ground->img->y;
	mlx_put_image_to_window(so->mlx, so->win, so->ground_tmp->img->ptr,
		so->ground_tmp->img->x, so->ground_tmp->img->y);
}

t_pt	prevent_zero_div(t_slng *so, t_pt p)
{
	p.x = so->ground->img->x - p.x;
	p.y = so->ground->img->y - p.y;
	p.x += (p.x == 0) * ((p.y / 8) - so->ground->img->y);
	p.y += (p.y == 0) * ((p.x / 8) - so->ground->img->x);
	return (p);
}

t_pt	get_displacement(t_slng *so)
{
	t_pt	ground;
	t_pt	player;

	ground = (t_pt){so->ground->img->x, so->ground->img->y};
	player = (t_pt){so->player->img->x, so->player->img->y};
	while (((ground.x + so->ground->img->width) >= so->width
			&& player.x > (so->width / 2) + so->player->img->width)
		|| (player.y > (so->height / 2) + so->player->img->height
			&& (ground.y + so->ground->img->height) >= so->height))
	{
		if ((player.x) > (so->width / 2) + so->player->img->width
			&& (ground.x + so->ground->img->width) >= so->width)
		{
			ground.x -= 1;
			player.x -= 1;
		}
		if (player.y > (so->height / 2) + so->player->img->height
			&& (ground.y + so->ground->img->height) >= so->height)
		{
			ground.y -= 1;
			player.y -= 1;
		}
	}
	return (prevent_zero_div(so, ground));
}

void	center_player_in_window(t_slng *so)
{
	t_pt	ground_diff;
	t_pt	delta;
	t_img	layer;

	if ((so->player->img->x + so->player->img->width) > so->width
		|| (so->player->img->y + so->player->img->height) > so->height)
	{
		ground_diff = get_displacement(so);
		layer = get_exit_layer(so, so->ground_full->img);
		insert_layer_in_image(so, so->ground_tmp->img, layer);
		delta = (t_pt){ground_diff.x / ground_diff.y, 1};
		if (ground_diff.y > ground_diff.x)
			delta = (t_pt){1, ground_diff.y / ground_diff.x};
		while (((so->player->img->x) > (so->width / 2) + so->player->img->width
				&& (so->ground->img->x
					+ so->ground->img->width >= so->width + delta.x))
			|| (so->player->img->y > (so->height / 2) + so->player->img->height
				&& (so->ground->img->y
					+ so->ground->img->height >= so->height + delta.y)))
			displace_ground_n_players(so, delta);
		insert_image_to(so->ground_tmp->img,
			so->ground_full->img, (t_pt){0, 0});
	}
}
