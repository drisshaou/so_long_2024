/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_all_images2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:44:39 by drhaouha          #+#    #+#             */
/*   Updated: 2024/08/02 08:22:14 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	process_xpm_image(t_slng *so, t_img **img, char *path)
{
	(*img)->ptr = mlx_xpm_file_to_image(so->mlx, path, &(*img)->width,
			&(*img)->height);
	if ((*img)->ptr == NULL)
		return (false);
	(*img)->data = mlx_get_data_addr((*img)->ptr, &(*img)->bpp,
			&(*img)->size_line, &(*img)->endian);
	return (true);
}

bool	add_numeric_images_next(t_slng *so, char *textures[11])
{
	int		i;

	i = -1;
	while (++i <= 10)
	{
		so->numeric->ptrs[i] = mlx_xpm_file_to_image(so->mlx,
				textures[i], &so->numeric->img->width,
				&so->numeric->img->height);
		if (so->numeric->ptrs[i] == NULL)
			return (false);
	}
	return (true);
}

bool	add_numeric_images(t_slng *so)
{
	static char	*textures[] = {"./xpm/zero.xpm", "./xpm/one.xpm",
		"./xpm/two.xpm", "./xpm/three.xpm", "./xpm/four.xpm",
		"./xpm/five.xpm", "./xpm/six.xpm", "./xpm/seven.xpm",
		"./xpm/eight.xpm", "./xpm/nine.xpm", "./xpm/empty.xpm"};

	if (!add_numeric_images_next(so, textures))
		return (false);
	return (true);
}

bool	add_ground_images(t_slng *so)
{
	if (!process_xpm_image(so, &so->ladder, "./xpm/ladder.xpm")
		|| !process_xpm_image(so, &so->point, "./xpm/point.xpm")
		|| !process_xpm_image(so, &so->cherry, "./xpm/cherry.xpm")
		|| !process_xpm_image(so, &so->cherry_fg, "./xpm/cherry_fg.xpm")
		|| !process_xpm_image(so, &so->cherry_bg, "./xpm/cherry_bg.xpm")
		|| !process_xpm_image(so, &so->floor, "./xpm/floor.xpm")
		|| !process_xpm_image(so, &so->grey_cube, "./xpm/grey_cube.xpm")
		|| !process_xpm_image(so, &so->blue_cube, "./xpm/blue_cube.xpm")
		|| !process_xpm_image(so, &so->game_over, "./xpm/game_over.xpm")
		|| !process_xpm_image(so, &so->you_win, "./xpm/you_win.xpm"))
		return (false);
	return (true);
}
