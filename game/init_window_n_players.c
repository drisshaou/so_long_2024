/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window_n_players.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:51:25 by drhaouha          #+#    #+#             */
/*   Updated: 2024/08/02 08:22:14 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_coord	get_coord_in_map(t_slng *so, char id)
{
	t_coord	coord;

	coord = (t_coord){-1, -1};
	while (so->map[++coord.row] != NULL)
	{
		coord.col = -1;
		while (so->map[coord.row][++coord.col] != '\0')
		{
			if (so->map[coord.row][coord.col] == id)
				return (coord);
		}
	}
	return ((t_coord){0, 0});
}

t_pt	get_pos_in_ground(t_slng *so, t_dim d, char id)
{
	t_coord	cur;
	int		gap;
	t_pt	pos;

	d.cols = ((12 * d.rows) + (d.cols * 40)) / 40;
	gap = ((12 * d.rows) / 40);
	cur.row = -1;
	pos = (t_pt){0, 0};
	while (++cur.row < d.rows)
	{
		cur.col = -1;
		while (++cur.col < d.cols)
		{
			pos = (t_pt){(-12 * (cur.row)) + (cur.col * 40), cur.row * 24};
			if (cur.col >= gap && so->map[cur.row][cur.col - gap] == id)
				return (pos);
		}
	}
	return (pos);
}

void	init_ghost(t_slng *so)
{
	t_pt	pos;
	t_coord	coord;

	so->ghost->id = 'G';
	pos = get_pos_in_ground(so, *so->map_dim, so->ghost->id);
	so->ghost->img->y = pos.y;
	so->ghost->img->x = pos.x;
	so->ghost->img->_y = so->ghost->img->y;
	so->ghost->img->_x = so->ghost->img->x;
	so->ghost->direction = 2;
	so->ghost->up = false;
	so->ghost->down = false;
	so->ghost->left = false;
	so->ghost->right = false;
	coord = get_coord_in_map(so, so->ghost->id);
	so->ghost->row = coord.row;
	so->ghost->col = coord.col;
	so->ghost->collected = 0;
	so->ghost->is_moving = false;
}

void	init_player(t_slng *so)
{
	t_pt	pos;
	t_coord	coord;

	so->player->id = 'P';
	pos = get_pos_in_ground(so, *so->map_dim, so->player->id);
	so->player->img->y = pos.y;
	so->player->img->x = pos.x;
	so->player->img->_y = so->player->img->y;
	so->player->img->_x = so->player->img->x;
	so->player->direction = 2;
	so->player->up = false;
	so->player->down = false;
	so->player->left = false;
	so->player->right = false;
	so->player->frame = 0;
	so->player->counter = 0;
	coord = get_coord_in_map(so, so->player->id);
	so->player->row = coord.row;
	so->player->col = coord.col;
	so->player->collected = 0;
	so->player->is_moving = false;
}

void	init_window_n_players(t_slng *so)
{
	so->width = WIDTH;
	so->height = HEIGHT;
	so->ground->img->x = 0;
	so->ground->img->y = 0;
	if (so->ground->img->width <= so->width)
		so->width = so->ground->img->width;
	if (so->ground->img->height <= so->height)
		so->height = so->ground->img->height;
	init_player(so);
	init_ghost(so);
	so->finished = false;
	so->has_ghost = true;
	if (so->ghost->row == 0 && so->ghost->col == 0)
		so->has_ghost = false;
}
