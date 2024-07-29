/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:36:11 by drhaouha          #+#    #+#             */
/*   Updated: 2024/07/29 09:10:16 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	prepare_memory(t_slng *so)
{
	if (!malloc_init_map_dim(so))
		return (ft_putstr(ERR_ALLOC_MEM), progressive_free(so, 1));
	if (!malloc_init_exit(so))
		return (ft_putstr(ERR_ALLOC_MEM), progressive_free(so, 2));
	if (!malloc_init_collect(so))
		return (ft_putstr(ERR_ALLOC_MEM), progressive_free(so, 3));
	if (!malloc_playgrounds(so))
		return (ft_putstr(ERR_ALLOC_MEM), progressive_free(so, 4));
	if (!malloc_player(so))
		return (ft_putstr(ERR_ALLOC_MEM), progressive_free(so, 5));
	if (!malloc_ghost(so))
		return (ft_putstr(ERR_ALLOC_MEM), progressive_free(so, 6));
	if (!malloc_numeric(so))
		return (ft_putstr(ERR_ALLOC_MEM), progressive_free(so, 7));
	if (!malloc_playground_images(so))
		return (ft_putstr(ERR_ALLOC_MEM), progressive_free(so, 8));
	return (true);
}

int	try_game(char ***map)
{
	t_slng	*so;

	so = (t_slng *)malloc(sizeof(t_slng));
	if (so == NULL)
		return (ft_putstr(ERR_ALLOC_MEM), 0);
	so->mlx = mlx_init();
	if (so->mlx == NULL)
		return (ft_putstr(ERR_MLX_INIT), 0);
	so->win = NULL;
	so->map = *map;
	if (so->map == NULL || (so->map && !prepare_memory(so)))
		return (mlx_destroy_display(so->mlx), free_slng(so, 0), exit(0), 0);
	if (!add_all_images(so) || !set_playgrounds(so))
		return (exit_game(so));
	init_window_n_players(so);
	so->win = mlx_new_window(so->mlx, so->width, so->height, "so_long");
	if (so->win == NULL)
		return (exit_game(so));
	center_player_in_window(so);
	mlx_hook(so->win, 3, 1L << 1, key_release, so);
	mlx_hook(so->win, 17, 0, exit_game, so);
	mlx_loop_hook(so->mlx, game_loop, so);
	mlx_loop(so->mlx);
	return (exit_game(so));
}
