/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:23:59 by drhaouha          #+#    #+#             */
/*   Updated: 2024/07/29 07:36:13 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

bool	check_map_elem(char **map, t_coord *begin)
{
	t_coord		pos;
	t_count		el;

	el = (t_count){0, 0, 0, 0};
	pos.row = -1;
	while (map[++pos.row] != NULL)
	{
		pos.col = -1;
		while (map[pos.row][++pos.col] != '\0')
		{
			if (map[pos.row][pos.col] == 'P')
				*begin = (t_coord){pos.col, pos.row};
			el.player += (map[pos.row][pos.col] == 'P');
			el.item += (map[pos.row][pos.col] == 'C');
			el.exit += (map[pos.row][pos.col] == 'E');
			el.others += (ft_strchr("01GPCE", map[pos.row][pos.col]) == NULL);
		}
	}
	return (validate_elem(el));
}

bool	check_map_sides(char **map)
{
	t_coord	pos;
	int		len;

	pos.row = 0;
	len = ft_strlen(map[pos.row]);
	while (map[pos.row] != NULL)
	{
		if (map[pos.row][0] != '1' || map[pos.row][len - 1] != '1')
			return (ft_putstr(ERR_INCORR_MAP), false);
		pos.row++;
	}
	pos.col = 0;
	while (map[0][pos.col])
	{
		if (map[0][pos.col] != '1' || map[pos.row - 1][pos.col] != '1')
			return (ft_putstr(ERR_INCORR_MAP), false);
		pos.col++;
	}
	return (true);
}

char	**mapdup(char **map)
{
	char	**tab;
	int		row;

	row = 0;
	while (map[row] != NULL)
		row++;
	tab = (char **)malloc(sizeof(char *) * (row + 1));
	if (tab == NULL)
		return (ft_putstr(ERR_ALLOC_MEM), NULL);
	row = -1;
	while (map[++row] != NULL)
	{
		tab[row] = ft_strdup(map[row]);
		if (tab[row] == NULL)
		{
			while (--row >= 0)
				free(tab[row]);
			free(tab);
			return (ft_putstr(ERR_ALLOC_MEM), NULL);
		}
	}
	tab[row] = NULL;
	return (tab);
}

bool	check_map(char **map)
{
	char		**tab;
	t_coord		begin;
	t_dim		d;

	d.rows = 0;
	if (map == NULL || map[d.rows] == NULL)
		return (ft_putstr(ERR_EMPTY_MAP), false);
	d.cols = (int)ft_strlen(map[d.rows]);
	while (map[++d.rows] != NULL)
	{
		if (d.cols != (int)ft_strlen(map[d.rows]))
			return (ft_putstr(ERR_MAP_UNRECT), false);
		d.cols = (int)ft_strlen(map[d.rows]);
	}
	tab = mapdup(map);
	begin = (t_coord){0, 0};
	if (tab == NULL || !check_map_sides(tab) || !check_map_elem(tab, &begin))
		return (free_map(&tab), false);
	if (!validate_flood(tab, (t_coord){d.cols, d.rows}, begin))
		return (free_map(&tab), false);
	free_map(&tab);
	return (true);
}
