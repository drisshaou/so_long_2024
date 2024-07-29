/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:54:20 by drhaouha          #+#    #+#             */
/*   Updated: 2024/07/29 08:46:11 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_map_content(t_slng *so, t_player *which, t_coord coord)
{
	if (so->exit->row == coord.row && so->exit->col == coord.col)
		so->map[coord.row][coord.col] = 'E';
	else if (so->collect[coord.row][coord.col] == true)
		so->map[coord.row][coord.col] = 'C';
	else
		so->map[coord.row][coord.col] = '0';
	if ((which->col == so->player->col && which->row == so->player->row
			&& which->id == 'G')
		|| (which->col == so->ghost->col && which->row == so->ghost->row
			&& which->id == 'P'))
		game_is_over(so);
	if (which->collected == so->collectibes && which->id == 'P'
		&& which->row == so->exit->row && which->col == so->exit->col)
		you_win(so);
	if (so->map[which->row][which->col] == 'C' && which->id == 'P')
	{
		so->collect[which->row][which->col] = false;
		which->collected++;
	}
	so->map[which->row][which->col] = which->id;
	if (which->id == 'P')
		which->counter++;
}

void	keep_player_inside(t_slng *so)
{
	if (so->player->img->x > (so->width - so->player->img->width))
		so->player->img->x = so->width - so->player->img->width;
	if (so->player->img->y > (so->height - so->player->img->height))
		so->player->img->y = so->height - so->player->img->height;
	so->player->img->x = !(so->player->img->x < 0) * so->player->img->x;
	so->player->img->y = !(so->player->img->y < 0) * so->player->img->y;
}

void	playground_n_players_left_right_adjust(t_slng *so)
{
	if (so->player->img->x > (so->width - so->player->img->width)
		&& so->playground->img->x > -(so->playground->img->width - so->width))
	{
		if (so->player->up)
			so->playground->img->x -= STEP;
		else
			so->playground->img->x -= STEP * 2;
		so->ghost->img->x -= STEP * (2 - so->player->up);
	}
	else if (so->player->img->x < 0 && so->playground->img->x < 0)
	{
		if (so->player->down)
			so->playground->img->x += STEP;
		else
			so->playground->img->x += STEP * 2;
		so->ghost->img->x += STEP * (2 - so->player->down);
	}
}

void	playground_n_players_up_down_adjust(t_slng *so)
{
	if (so->player->img->y > (so->height - so->player->img->height)
		&& so->playground->img->y > -(so->playground->img->height - so->height)
		&& so->playground->img->x <= 0)
	{
		so->playground->img->y -= STEP * 2;
		if (so->playground->img->x < 0)
			so->playground->img->x += STEP;
		else if (so->player->down)
			so->player->img->x -= STEP;
		so->ghost->img->y -= STEP * 2;
		if (so->playground->img->x < 0)
			so->ghost->img->x += STEP;
	}
	else if (so->player->img->y < 0 && so->playground->img->y < 0
		&& so->playground->img->x >= -(so->playground->img->width - so->width))
	{
		so->playground->img->y += STEP * 2;
		if (so->playground->img->x > -(so->playground->img->width - so->width))
			so->playground->img->x -= STEP;
		else if (so->player->up)
			so->player->img->x += STEP;
		so->ghost->img->y += STEP * 2;
		if (so->playground->img->x > -(so->playground->img->width - so->width))
			so->ghost->img->x -= STEP;
	}
}

void	animate_player(t_slng *so, t_player *which)
{
	which->img->x += (STEP * 2 * (which->right - which->left));
	which->img->y += (STEP * 2 * (which->down - which->up));
	if ((which->img->y >= 0
			&& which->img->y <= (so->height - which->img->height))
		&& (which->img->x >= 0
			&& which->img->x <= (so->width - which->img->width)))
		which->img->x += (STEP * (which->up - which->down));
	if (which->id == 'P')
	{
		playground_n_players_left_right_adjust(so);
		playground_n_players_up_down_adjust(so);
		keep_player_inside(so);
	}
	which->img->_x = which->img->x;
	which->img->_x -= (STEP * 2
			* (which->right - which->left));
	which->img->_y = which->img->y;
	which->img->_y -= (STEP * 2
			* (which->down - which->up));
	draw_frame(so);
}
