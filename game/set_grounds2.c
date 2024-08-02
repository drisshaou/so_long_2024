/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_grounds2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:48:45 by drhaouha          #+#    #+#             */
/*   Updated: 2024/08/01 08:35:00 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	add_walls(t_slng *so, t_dim d)
{
	t_coord	cur;
	t_pt	pos;
	int		gap;

	d.cols = ((12 * d.rows) + (d.cols * 40)) / 40;
	gap = ((12 * d.rows) / 40);
	cur.row = -1;
	while (++cur.row < d.rows)
	{
		cur.col = -1;
		while (++cur.col < d.cols)
		{
			if (cur.col >= gap && so->map[cur.row][cur.col - gap] == '1')
			{
				pos = (t_pt){(-12 * cur.row) + (cur.col * 40), cur.row * 24};
				if (((cur.col - gap) + cur.row) % 2 == 0)
					insert_image_to(so->ground->img, so->grey_cube, pos);
				else
					insert_image_to(so->ground->img, so->blue_cube, pos);
			}
		}
	}
}

void	add_floor(t_slng *so, t_dim d)
{
	t_coord	cur;
	t_pt	pos;

	d.cols = ((12 * 2 * (d.rows + 1)) + (d.cols * 40)) / 40;
	cur.row = -1;
	while (++cur.row < d.rows + 1)
	{
		cur.col = -1;
		while (++cur.col < d.cols)
		{
			pos = (t_pt){(-12 * cur.row) + (cur.col * 40), cur.row * 24};
			insert_image_to(so->ground->img, so->floor, pos);
		}
	}
}

// void	add_collectibles(t_slng *so, t_dim d)
// {
// 	t_coord	cur;
// 	t_pt	pos;
// 	int		gap;

// 	d.cols = ((12 * d.rows) + (d.cols * 40)) / 40;
// 	gap = ((12 * d.rows) / 40);
// 	cur.row = -1;
// 	while (++cur.row < d.rows)
// 	{
// 		cur.col = -1;
// 		while (++cur.col < d.cols)
// 		{
// 			pos = (t_pt){(-12 * cur.row) + (cur.col * 40), cur.row * 24};
// 			if (cur.col >= gap && so->map[cur.row][cur.col - gap] != '1')
// 			{
// 				insert_image_to(so->ground_full->img, so->point, pos);
// 				if (cur.col >= gap && so->map[cur.row][cur.col - gap] == 'C')
// 				{
// 					insert_image_to(so->ground_full->img, so->cherry, pos);
// 					so->collectibes++;
// 					so->collect[cur.row][cur.col - gap] = true;
// 				}
// 			}
// 		}
// 	}
// }

void	add_collectibles(t_slng *so, t_dim d)
{
	t_coord	cur;
	t_pt	pos;
	int		gap;

	d.cols = ((12 * d.rows) + (d.cols * 40)) / 40;
	gap = ((12 * d.rows) / 40);
	cur.row = -1;
	while (++cur.row < d.rows)
	{
		cur.col = -1;
		while (++cur.col < d.cols)
		{
			pos = (t_pt){(-12 * cur.row) + (cur.col * 40), cur.row * 24};
			if (cur.col >= gap && so->map[cur.row][cur.col - gap] == '0')
				insert_image_to(so->ground_full->img, so->point, pos);
			if (cur.col >= gap && so->map[cur.row][cur.col - gap] == 'C')
			{
				insert_image_to(so->ground_full->img, so->cherry, pos);
				so->collectibes++;
				so->collect[cur.row][cur.col - gap] = true;
			}
		}
	}
}

bool	set_ground_tmp(t_slng *so)
{
	so->ground_tmp->img->width = so->ground_full->img->width;
	so->ground_tmp->img->height = so->ground_full->img->height;
	so->ground_tmp->img->ptr = mlx_new_image(so->mlx,
			so->ground_tmp->img->width,
			so->ground_tmp->img->height);
	if (so->ground_tmp->img->ptr == NULL)
		return (false);
	so->ground_tmp->img->data = mlx_get_data_addr(
			so->ground_tmp->img->ptr,
			&so->ground_tmp->img->bpp,
			&so->ground_tmp->img->size_line,
			&so->ground_tmp->img->endian);
	insert_image_to(so->ground_tmp->img,
		so->ground_full->img, (t_pt){0, 0});
	return (true);
}

bool	set_ground_full(t_slng *so)
{
	so->ground_full->img->width = so->ground->img->width;
	so->ground_full->img->height = so->ground->img->height;
	so->ground_full->img->ptr = mlx_new_image(so->mlx,
			so->ground_full->img->width,
			so->ground_full->img->height);
	if (so->ground_full->img->ptr == NULL)
		return (false);
	so->ground_full->img->data = mlx_get_data_addr(
			so->ground_full->img->ptr,
			&so->ground_full->img->bpp,
			&so->ground_full->img->size_line,
			&so->ground_full->img->endian);
	insert_image_to(so->ground_full->img,
		so->ground->img, (t_pt){0, 0});
	add_collectibles(so, *so->map_dim);
	if (!set_ground_tmp(so))
		return (false);
	return (true);
}
