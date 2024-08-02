/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_n_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:23:59 by drhaouha          #+#    #+#             */
/*   Updated: 2024/07/31 15:36:16 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_flooded_map(char **map, t_coord cur)
{
	t_coord	pos;

	pos.row = -1;
	while (map[++pos.row] != NULL)
	{
		pos.col = -1;
		while (map[pos.row][++pos.col])
		{
			if (cur.row == pos.row && cur.col == pos.col)
			{
				write(STDOUT_FILENO, "\033[0;31m", 8);
				write(STDOUT_FILENO, &map[pos.row][pos.col], 1);
				write(STDOUT_FILENO, "\033[0m", 5);
			}
			else
				write(STDOUT_FILENO, &map[pos.row][pos.col], 1);
		}
		write(STDOUT_FILENO, "\n", 1);
	}
	write(STDOUT_FILENO, "\n", 1);
}

void	flood_fill(char **map, t_coord size, t_coord cur, char *str)
{
	if (cur.row < 0 || cur.row >= size.row
		|| cur.col < 0 || cur.col >= size.col)
		return ;
	if (ft_strchr(str, map[cur.row][cur.col]) != NULL)
		map[cur.row][cur.col] = '1';
	else
		return ;
	flood_fill(map, size, (t_coord){cur.col - 1, cur.row}, str);
	flood_fill(map, size, (t_coord){cur.col + 1, cur.row}, str);
	flood_fill(map, size, (t_coord){cur.col, cur.row - 1}, str);
	flood_fill(map, size, (t_coord){cur.col, cur.row + 1}, str);
}

bool	validate_flood(char **map, t_coord size, t_coord begin)
{
	t_coord		pos;

	flood_fill(map, size, begin, "0PCE");
	pos.row = -1;
	while (map[++pos.row] != NULL)
	{
		pos.col = -1;
		while (map[pos.row][++pos.col] != '\0')
		{
			if (ft_strchr("PCE", map[pos.row][pos.col]) != NULL)
			{
				ft_putstr(ERR_UNREACH_EL);
				return (false);
			}
		}
	}
	return (true);
}

bool	validate_elem(t_count el)
{
	if (el.player != 1 || el.exit != 1
		|| el.item == 0 || el.others > 0)
	{
		ft_putstr(ERR);
		if (el.player == 0)
			ft_putstr(ERR_NO_PLAYER);
		else if (el.player > 1)
			ft_putstr(ERR_MORE_PLAYER);
		if (el.item == 0)
			ft_putstr(ERR_NO_ITEM);
		if (el.exit == 0)
			ft_putstr(ERR_NO_EXIT);
		else if (el.exit > 1)
			ft_putstr(ERR_MORE_EXIT);
		if (el.others > 0)
			ft_putstr(ERR_OTHER_EL);
		return (false);
	}
	return (true);
}
