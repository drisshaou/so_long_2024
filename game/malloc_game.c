/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:38:36 by drhaouha          #+#    #+#             */
/*   Updated: 2024/07/29 09:03:56 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	malloc_ghost(t_slng *so)
{
	int	i;

	so->ghost = (t_player *)malloc(sizeof(t_player));
	if (so->ghost == NULL)
		return (false);
	if (!malloc_img(&so->ghost->img))
		return (false);
	i = -1;
	while (++i < 4)
		so->ghost->ptrs[i][0] = NULL;
	return (true);
}

bool	malloc_player(t_slng *so)
{
	int	i;
	int	j;

	so->player = (t_player *)malloc(sizeof(t_player));
	if (so->player == NULL)
		return (false);
	if (!malloc_img(&so->player->img))
		return (false);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 6)
			so->player->ptrs[i][j] = NULL;
	}
	return (true);
}

bool	malloc_init_collect(t_slng *so)
{
	t_coord	cur;

	so->collect = (bool **)malloc(sizeof(bool *) * so->map_dim->rows);
	cur.row = -1;
	so->collectibes = 0;
	while (++cur.row < so->map_dim->rows)
	{
		so->collect[cur.row] = (bool *)malloc(sizeof(bool) * so->map_dim->cols);
		if (so->collect[cur.row] == NULL)
		{
			while (--cur.row >= 0)
				free(so->collect[cur.row]);
			free(so->collect);
			return (false);
		}
		cur.col = -1;
		while (++cur.col < so->map_dim->cols)
			so->collect[cur.row][cur.col] = false;
	}
	return (true);
}

bool	malloc_init_exit(t_slng *so)
{
	t_coord	coord;

	so->exit = (t_coord *)malloc(sizeof(t_coord));
	if (so->exit == NULL)
		return (false);
	coord = get_coord_in_map(so, 'E');
	so->exit->row = coord.row;
	so->exit->col = coord.col;
	return (true);
}

bool	malloc_init_map_dim(t_slng *so)
{
	t_dim	d;

	so->map_dim = (t_dim *)malloc(sizeof(t_dim));
	if (so->map_dim == NULL)
		return (false);
	d = get_map_dimension(so);
	so->map_dim->rows = d.rows;
	so->map_dim->cols = d.cols;
	return (true);
}
