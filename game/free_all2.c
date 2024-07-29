/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:09:17 by drhaouha          #+#    #+#             */
/*   Updated: 2024/07/29 08:34:09 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char ***map)
{
	int	row;

	if (*map != NULL)
	{
		row = 0;
		while ((*map)[row] != NULL)
		{
			if ((*map)[row] != NULL)
				free((*map)[row]);
			(*map)[row] = NULL;
			row++;
		}
		if (*map != NULL)
			free(*map);
		*map = NULL;
	}
}

void	free_collect(bool ***collect, t_dim d)
{
	int		row;

	row = 0;
	while (row < d.rows)
	{
		if ((*collect)[row] != NULL)
			free((*collect)[row]);
		(*collect)[row] = NULL;
		row++;
	}
	if (*collect != NULL)
		free(*collect);
	*collect = NULL;
}

void	free_playgrounds(t_slng *so)
{
	if (so->playground->img != NULL)
		free(so->playground->img);
	if (so->playground != NULL)
		free(so->playground);
	if (so->playground_full->img != NULL)
		free(so->playground_full->img);
	if (so->playground_full != NULL)
		free(so->playground_full);
	if (so->playground_tmp->img != NULL)
		free(so->playground_tmp->img);
	if (so->playground_tmp != NULL)
		free(so->playground_tmp);
}

void	free_player(t_slng *so)
{
	if (so->player->img != NULL)
		free(so->player->img);
	if (so->player != NULL)
		free(so->player);
}
