/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:54:20 by drhaouha          #+#    #+#             */
/*   Updated: 2024/07/31 06:44:27 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	process_ghost(t_slng *so)
{
	static int	frame_count = 0;
	t_coord		coord;
	int			loop;

	if (++frame_count < 28)
		return ;
	frame_count = 0;
	coord = (t_coord){so->ghost->col, so->ghost->row};
	if (move_towards_player(so))
	{
		loop = (so->ghost->left || so->ghost->right) * 20
			+ (so->ghost->up || so->ghost->down) * 12;
		while (loop > 0)
		{
			so->ghost->is_moving = true;
			animate_player(so, so->ghost);
			__timer(5000000);
			loop--;
		}
		update_map_content(so, so->ghost, coord);
	}
	reset_move(so->ghost);
	so->ghost->is_moving = false;
}

void	process_player(t_slng *so)
{
	static int	frame_count = 0;
	t_coord		coord;
	int			loop;

	if (++frame_count < 6)
		return ;
	frame_count = 0;
	coord = (t_coord){so->player->col, so->player->row};
	if (is_next_coord_valid(so, so->player, coord))
	{
		loop = (so->player->left || so->player->right) * 20
			+ (so->player->up || so->player->down) * 12;
		so->player->frame = 0;
		while (loop > 0)
		{
			so->player->is_moving = true;
			animate_player(so, so->player);
			__timer(5000000);
			loop--;
		}
		update_map_content(so, so->player, coord);
	}
	reset_move(so->player);
	so->player->is_moving = false;
}

int	game_loop(t_slng *so)
{
	static int	frame_count = 0;

	if (++frame_count < 1)
		return (0);
	frame_count = 0;
	if (so->has_ghost && !so->ghost->is_moving)
		process_ghost(so);
	if (!so->player->is_moving)
		process_player(so);
	draw_frame(so);
	return (1);
}
