/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_game2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 06:38:36 by drhaouha          #+#    #+#             */
/*   Updated: 2024/08/02 08:22:14 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_dim	get_map_dimension(t_slng *so)
{
	t_dim	d;

	d = (t_dim){0, 0};
	while (so->map[d.rows] != NULL)
		d.rows++;
	d.cols = ft_strlen(so->map[d.rows - 1]);
	return (d);
}

bool	malloc_img(t_img **img)
{
	*img = NULL;
	*img = (t_img *)malloc(sizeof(t_img));
	if (*img == NULL)
		return (false);
	(*img)->ptr = NULL;
	return (true);
}

bool	malloc_grounds(t_slng *so)
{
	so->ground = NULL;
	so->ground_full = NULL;
	so->ground_tmp = NULL;
	so->ground = (t_pground *)malloc(sizeof(t_pground));
	if (so->ground == NULL)
		return (false);
	if (!malloc_img(&so->ground->img))
		return (false);
	so->ground_full = (t_pground *)malloc(sizeof(t_pground));
	if (so->ground_full == NULL)
		return (false);
	if (!malloc_img(&so->ground_full->img))
		return (false);
	so->ground_tmp = (t_pground *)malloc(sizeof(t_pground));
	if (so->ground_tmp == NULL)
		return (false);
	if (!malloc_img(&so->ground_tmp->img))
		return (false);
	return (true);
}

bool	malloc_ground_images(t_slng *so)
{
	if (!malloc_img(&so->ladder)
		|| !malloc_img(&so->point)
		|| !malloc_img(&so->cherry)
		|| !malloc_img(&so->cherry_fg)
		|| !malloc_img(&so->cherry_bg)
		|| !malloc_img(&so->floor)
		|| !malloc_img(&so->grey_cube)
		|| !malloc_img(&so->blue_cube)
		|| !malloc_img(&so->game_over)
		|| !malloc_img(&so->you_win))
		return (false);
	return (true);
}

bool	malloc_numeric(t_slng *so)
{
	int	i;

	so->numeric = (t_num *)malloc(sizeof(t_num));
	if (so->numeric == NULL)
		return (false);
	if (!malloc_img(&so->numeric->img))
		return (false);
	i = -1;
	while (++i <= 10)
		so->numeric->ptrs[i] = NULL;
	return (true);
}
