/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:54:20 by drhaouha          #+#    #+#             */
/*   Updated: 2024/08/02 08:25:10 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_map_content(t_slng *so, t_player *which, t_coord coord)
{
	if (which->id == 'P')
	{
		ft_putstr("move(s): ");
		ft_putnbr(++which->counter);
		ft_putstr("\n");
	}
	if (so->exit->row == coord.row && so->exit->col == coord.col)
		so->map[coord.row][coord.col] = 'E';
	else if (so->collect[coord.row][coord.col] == true)
		so->map[coord.row][coord.col] = 'C';
	else
		so->map[coord.row][coord.col] = '0';
	if (so->player->col == so->ghost->col && so->player->row == so->ghost->row)
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
}

void	keep_player_inside(t_slng *so, t_player *which)
{
	if (which->img->x > (so->width - (2 * which->img->width)))
		which->img->x = so->width - (2 * which->img->width);
	if (which->img->y > (so->height - (2 * which->img->height)))
		which->img->y = so->height - (2 * which->img->height);
	which->img->x = !(which->img->x < which->img->width) * which->img->x;
	which->img->y = !(which->img->y < which->img->height) * which->img->y;
	which->img->x += (which->img->x < which->img->width) * which->img->width;
	which->img->y += (which->img->y < which->img->height) * which->img->height;
}

void	ground_n_players_left_right_adjust(t_slng *so, t_player *which)
{
	if (which->img->x > (so->width - (2 * which->img->width))
		&& so->ground->img->x > -(so->ground->img->width - so->width))
	{
		if (which->up)
			so->ground->img->x -= STEP;
		else
			so->ground->img->x -= STEP * 2;
		so->ghost->img->x -= STEP * (2 - which->up);
	}
	else if (which->img->x < which->img->width && so->ground->img->x < 0)
	{
		if (which->down)
			so->ground->img->x += STEP;
		else
			so->ground->img->x += STEP * 2;
		so->ghost->img->x += STEP * (2 - which->down);
	}
}

void	ground_n_players_up_down_adjust(t_slng *so, t_player *which)
{
	if (which->img->y > (so->height - (2 * which->img->height))
		&& so->ground->img->y > -(so->ground->img->height - so->height)
		&& so->ground->img->x < 0)
	{
		so->ground->img->y -= STEP * 2;
		if (so->ground->img->x < 0)
			so->ground->img->x += STEP;
		else if (which->down)
			which->img->x -= STEP;
		so->ghost->img->y -= STEP * 2;
		if (so->ground->img->x < 0)
			so->ghost->img->x += STEP;
	}
	else if (which->img->y < which->img->height && so->ground->img->y < 0
		&& so->ground->img->x > -(so->ground->img->width - so->width))
	{
		so->ground->img->y += STEP * 2;
		if (so->ground->img->x > -(so->ground->img->width - so->width))
			so->ground->img->x -= STEP;
		else if (which->up)
			which->img->x += STEP;
		so->ghost->img->y += STEP * 2;
		if (so->ground->img->x > -(so->ground->img->width - so->width))
			so->ghost->img->x -= STEP;
	}
}

void	animate_player(t_slng *so, t_player *which)
{
	which->img->x += (STEP * 2 * (which->right - which->left));
	which->img->y += (STEP * 2 * (which->down - which->up));
	if (((which->img->y >= which->img->height
				&& which->img->y <= (so->height - (2 * which->img->height)))
			&& (which->img->x >= which->img->width
				&& which->img->x <= (so->width - (2 * which->img->width)))
			&& which->id == 'P') || which->id == 'G')
		which->img->x += (STEP * (which->up - which->down));
	if (which->id == 'P')
	{
		ground_n_players_left_right_adjust(so, which);
		ground_n_players_up_down_adjust(so, which);
		keep_player_inside(so, which);
	}
	which->img->_x = which->img->x;
	which->img->_x -= (STEP * 2
			* (which->right - which->left));
	which->img->_y = which->img->y;
	which->img->_y -= (STEP * 2
			* (which->down - which->up));
	draw_frame(so);
}
