/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:54:20 by drhaouha          #+#    #+#             */
/*   Updated: 2024/07/29 13:15:58 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	move_verticaly_first(t_slng *so, t_coord delta)
{
	t_coord	coord;

	coord = (t_coord){so->ghost->col, so->ghost->row};
	if (delta.row > 0)
		so->ghost->down = true;
	else
		so->ghost->up = true;
	if (is_next_coord_valid(so, so->ghost, coord))
	{
		set_move_direction(so->ghost);
		return (true);
	}
	so->ghost->down = false;
	so->ghost->up = false;
	if (delta.col > 0)
		so->ghost->right = true;
	else
		so->ghost->left = true;
	if (is_next_coord_valid(so, so->ghost, coord))
	{
		set_move_direction(so->ghost);
		return (true);
	}
	return (false);
}

bool	move_horizontaly_first(t_slng *so, t_coord delta)
{
	t_coord	coord;

	coord = (t_coord){so->ghost->col, so->ghost->row};
	if (delta.col > 0)
		so->ghost->right = true;
	else
		so->ghost->left = true;
	if (is_next_coord_valid(so, so->ghost, coord))
	{
		set_move_direction(so->ghost);
		return (true);
	}
	so->ghost->right = false;
	so->ghost->left = false;
	if (delta.row > 0)
		so->ghost->down = true;
	else
		so->ghost->up = true;
	if (is_next_coord_valid(so, so->ghost, coord))
	{
		set_move_direction(so->ghost);
		return (true);
	}
	return (false);
}

int	_abs(int j)
{
	return (j * ((-(j < 0) * 2) + 1));
}

bool	move_towards_player(t_slng *so)
{
	t_coord	delta;

	delta.col = so->player->col - so->ghost->col;
	delta.row = so->player->row - so->ghost->row;
	if (so->ghost->is_moving)
		return (false);
	reset_move(so->ghost);
	if (so->player->col == so->ghost->col && so->player->row == so->ghost->row)
		return (false);
	if (_abs(delta.row) > _abs(delta.col))
		return (move_verticaly_first(so, delta));
	else
		return (move_horizontaly_first(so, delta));
	return (false);
}

bool	is_next_coord_valid(t_slng *so, t_player *which, t_coord coord)
{
	if (which->up
		&& so->map[which->row - 1][which->col] != '1')
		which->row--;
	else if (which->down
		&& so->map[which->row + 1][which->col] != '1')
		which->row++;
	else if (which->left
		&& so->map[which->row][which->col - 1] != '1')
		which->col--;
	else if (which->right
		&& so->map[which->row][which->col + 1] != '1')
		which->col++;
	if (!(coord.col == which->col && coord.row == which->row))
	{
		if (which->id == 'P')
		{
			ft_putstr("move(s): ");
			ft_putnbr(which->counter);
			ft_putstr("\n");
		}
		return (true);
	}
	return (false);
}
