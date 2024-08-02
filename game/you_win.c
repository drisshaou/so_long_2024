/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   you_win.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:01:22 by drhaouha          #+#    #+#             */
/*   Updated: 2024/08/02 08:22:14 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	__timer(unsigned long long i)
{
	while (i-- > 0)
		;
}

void	you_win_next(t_slng *so)
{
	int	j;

	j = 40;
	while (j-- > 0)
	{
		__timer(8000000);
		insert_image_to(so->ground_tmp->img, so->you_win,
			(t_pt){so->you_win->x - so->ground_tmp->img->x,
			so->you_win->y - so->ground_tmp->img->y});
		draw_frame(so);
	}
}

void	you_win(t_slng *so)
{
	int	j;
	int	k;

	j = -1;
	k = 1;
	so->finished = true;
	so->player->direction = 0;
	so->you_win->x = (so->width - so->you_win->width) / 2;
	so->you_win->y = (so->height - so->you_win->height) / 2;
	while (so->player->img->y + so->player->img->height > 0)
	{
		so->player->img->_y = so->player->img->y;
		so->player->img->y -= STEP * 2;
		j *= (-(k++ % 2 == 0) * 2 + 1);
		so->player->img->x += STEP * j;
		draw_frame(so);
		__timer(3000000);
	}
	you_win_next(so);
	exit_game(so);
}
