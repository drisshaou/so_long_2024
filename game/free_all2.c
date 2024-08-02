/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:09:17 by drhaouha          #+#    #+#             */
/*   Updated: 2024/08/02 08:22:14 by drhaouha         ###   ########.fr       */
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

void	free_grounds(t_slng *so)
{
	if (so->ground->img != NULL)
		free(so->ground->img);
	if (so->ground != NULL)
		free(so->ground);
	if (so->ground_full->img != NULL)
		free(so->ground_full->img);
	if (so->ground_full != NULL)
		free(so->ground_full);
	if (so->ground_tmp->img != NULL)
		free(so->ground_tmp->img);
	if (so->ground_tmp != NULL)
		free(so->ground_tmp);
}

void	free_player(t_slng *so)
{
	if (so->player->img != NULL)
		free(so->player->img);
	if (so->player != NULL)
		free(so->player);
}
