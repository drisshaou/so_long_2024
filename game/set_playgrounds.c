/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_playgrounds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:48:45 by drhaouha          #+#    #+#             */
/*   Updated: 2024/07/29 11:48:30 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	set_playgrounds(t_slng *so)
{
	so->playground->img->width = (so->map_dim->rows * 12)
		+ (40 * so->map_dim->cols);
	so->playground->img->height = (so->map_dim->rows * 24) + 24;
	mlx_get_screen_size(so->mlx, &so->screen_w, &so->screen_h);
	if (so->playground->img->width > (2 * so->screen_w)
		|| so->playground->img->height > (2 * so->screen_h))
		return (false);
	so->playground->img->ptr = mlx_new_image(so->mlx,
			so->playground->img->width,
			so->playground->img->height);
	if (so->playground->img->ptr == NULL)
		return (ft_putstr(ERR_ALLOC_MEM), false);
	so->playground->img->data = mlx_get_data_addr(
			so->playground->img->ptr,
			&so->playground->img->bpp,
			&so->playground->img->size_line,
			&so->playground->img->endian);
	add_floor(so, *so->map_dim);
	add_walls(so, *so->map_dim);
	if (!set_playground_full(so))
		return (ft_putstr(ERR_ALLOC_MEM), false);
	return (true);
}
