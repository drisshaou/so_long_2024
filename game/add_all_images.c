/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_all_images.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:44:39 by drhaouha          #+#    #+#             */
/*   Updated: 2024/07/29 07:59:38 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	add_ghost_images_next(t_slng *so, char *textures[4])
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		so->ghost->ptrs[i][0] = mlx_xpm_file_to_image(so->mlx,
				textures[i], &so->ghost->img->width, &so->ghost->img->height);
		if (so->ghost->ptrs[i][0] == NULL)
			return (false);
	}
	return (true);
}

bool	add_ghost_images(t_slng *so)
{
	static char	*textures[] = {"./xpm/ghost_u.xpm",
		"./xpm/ghost_r.xpm", "./xpm/ghost_d.xpm",
		"./xpm/ghost_l.xpm"};

	if (!add_ghost_images_next(so, textures))
		return (false);
	return (true);
}

bool	add_player_images_next(t_slng *so, char *textures[4][6])
{
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 6)
		{
			so->player->ptrs[i][j] = mlx_xpm_file_to_image(so->mlx,
					textures[i][j], &so->player->img->width,
					&so->player->img->height);
			if (so->player->ptrs[i][j] == NULL)
				return (false);
		}
	}
	return (true);
}

bool	add_player_images(t_slng *so)
{
	static char	*textures[4][6] = {
	{"./xpm/pacman_u0.xpm", "./xpm/pacman_u1.xpm",
		"./xpm/pacman_u2.xpm", "./xpm/pacman_u3.xpm",
		"./xpm/pacman_u4.xpm", "./xpm/pacman_u5.xpm"},
	{"./xpm/pacman_r0.xpm", "./xpm/pacman_r1.xpm",
		"./xpm/pacman_r2.xpm", "./xpm/pacman_r3.xpm",
		"./xpm/pacman_r4.xpm", "./xpm/pacman_r5.xpm"},
	{"./xpm/pacman_d0.xpm", "./xpm/pacman_d1.xpm",
		"./xpm/pacman_d2.xpm", "./xpm/pacman_d3.xpm",
		"./xpm/pacman_d4.xpm", "./xpm/pacman_d5.xpm"},
	{"./xpm/pacman_l0.xpm", "./xpm/pacman_l1.xpm",
		"./xpm/pacman_l2.xpm", "./xpm/pacman_l3.xpm",
		"./xpm/pacman_l4.xpm", "./xpm/pacman_l5.xpm"}};

	if (!add_player_images_next(so, textures))
		return (false);
	return (true);
}

bool	add_all_images(t_slng *so)
{
	if (!add_playground_images(so) || !add_numeric_images(so)
		|| !add_player_images(so) || !add_ghost_images(so))
	{
		ft_putstr(ERR_LOAD_TEXTURE);
		return (false);
	}
	return (true);
}
