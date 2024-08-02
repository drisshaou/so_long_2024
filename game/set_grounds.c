/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_grounds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:48:45 by drhaouha          #+#    #+#             */
/*   Updated: 2024/08/01 11:24:10 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	set_grounds(t_slng *so)
{
	so->ground->img->width = (so->map_dim->rows * 12)
		+ (40 * so->map_dim->cols);
	so->ground->img->height = (so->map_dim->rows * 24) + 24;
	mlx_get_screen_size(so->mlx, &so->screen_w, &so->screen_h);
	if (so->ground->img->width > (2 * so->screen_w)
		|| so->ground->img->height > (2 * so->screen_h))
		return (ft_putstr(MAP_TOO_BIG), false);
	so->ground->img->ptr = mlx_new_image(so->mlx,
			so->ground->img->width,
			so->ground->img->height);
	if (so->ground->img->ptr == NULL)
		return (ft_putstr(ERR_ALLOC_MEM), false);
	so->ground->img->data = mlx_get_data_addr(
			so->ground->img->ptr,
			&so->ground->img->bpp,
			&so->ground->img->size_line,
			&so->ground->img->endian);
	add_floor(so, *so->map_dim);
	add_walls(so, *so->map_dim);
	if (!set_ground_full(so))
		return (ft_putstr(ERR_ALLOC_MEM), false);
	return (true);
}
