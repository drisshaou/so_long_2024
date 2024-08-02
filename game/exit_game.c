/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:08:02 by drhaouha          #+#    #+#             */
/*   Updated: 2024/08/02 08:22:14 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_all_images_next(t_slng *so)
{
	int	i;
	int	j;

	if (so->ladder->ptr != NULL)
		mlx_destroy_image(so->mlx, so->ladder->ptr);
	i = -1;
	while (++i <= 10)
	{
		if (so->numeric->ptrs[i] != NULL)
			mlx_destroy_image(so->mlx, so->numeric->ptrs[i]);
	}
	i = -1;
	while (++i < 4)
	{
		if (so->ghost->ptrs[i][0] != NULL)
			mlx_destroy_image(so->mlx, so->ghost->ptrs[i][0]);
		j = -1;
		while (++j < 6)
		{
			if (so->player->ptrs[i][j] != NULL)
				mlx_destroy_image(so->mlx, so->player->ptrs[i][j]);
		}
	}
}

void	destroy_all_images(t_slng *so)
{
	if (so->ground->img->ptr != NULL)
		mlx_destroy_image(so->mlx, so->ground->img->ptr);
	if (so->ground_full->img->ptr != NULL)
		mlx_destroy_image(so->mlx, so->ground_full->img->ptr);
	if (so->ground_tmp->img->ptr != NULL)
		mlx_destroy_image(so->mlx, so->ground_tmp->img->ptr);
	if (so->floor->ptr != NULL)
		mlx_destroy_image(so->mlx, so->floor->ptr);
	if (so->grey_cube->ptr != NULL)
		mlx_destroy_image(so->mlx, so->grey_cube->ptr);
	if (so->blue_cube->ptr != NULL)
		mlx_destroy_image(so->mlx, so->blue_cube->ptr);
	if (so->point->ptr != NULL)
		mlx_destroy_image(so->mlx, so->point->ptr);
	if (so->cherry->ptr != NULL)
		mlx_destroy_image(so->mlx, so->cherry->ptr);
	if (so->cherry_fg->ptr != NULL)
		mlx_destroy_image(so->mlx, so->cherry_fg->ptr);
	if (so->cherry_bg->ptr != NULL)
		mlx_destroy_image(so->mlx, so->cherry_bg->ptr);
	if (so->game_over->ptr != NULL)
		mlx_destroy_image(so->mlx, so->game_over->ptr);
	if (so->you_win->ptr != NULL)
		mlx_destroy_image(so->mlx, so->you_win->ptr);
	destroy_all_images_next(so);
}

int	exit_game(t_slng *so)
{
	destroy_all_images(so);
	if (so->win != NULL)
		mlx_destroy_window(so->mlx, so->win);
	mlx_destroy_display(so->mlx);
	free_slng(so, 8);
	exit(0);
	return (0);
}
