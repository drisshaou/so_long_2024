/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:52:38 by drhaouha          #+#    #+#             */
/*   Updated: 2024/07/29 11:07:54 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_move_direction(t_player *which)
{
	which->direction = (which->left * 3);
	which->direction += (which->right);
	which->direction += (which->down * 2);
}

void	reset_move(t_player *which)
{
	which->right = false;
	which->left = false;
	which->up = false;
	which->down = false;
}

int	key_release(int keycode, t_slng *so)
{
	reset_move(so->player);
	if (keycode == KEY_ESC)
		exit_game(so);
	if (keycode == ARROW_LEFT || keycode == LETTER_LEFT)
		so->player->left = true;
	else if (keycode == ARROW_UP || keycode == LETTER_UP)
		so->player->up = true;
	else if (keycode == ARROW_RIGHT || keycode == LETTER_RIGHT)
		so->player->right = true;
	else if (keycode == ARROW_DOWN || keycode == LETTER_DOWN)
		so->player->down = true;
	set_move_direction(so->player);
	return (1);
}
