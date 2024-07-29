/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_n_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:23:59 by drhaouha          #+#    #+#             */
/*   Updated: 2024/07/29 07:34:37 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*get_map_line(int fd)
{
	int		i;
	size_t	len;
	char	*dest;
	char	*line;

	line = get_next_line(fd);
	if (line == NULL)
		return (NULL);
	len = ft_strlen(line) - (ft_strchr(line, '\n') != NULL);
	dest = (char *)malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		dest[i] = line[i];
		i++;
	}
	dest[i] = '\0';
	return (free(line), dest);
}

int	get_map_size(char const *path)
{
	int		fd;
	int		size;
	char	*line;

	fd = open(path, O_RDONLY);
	size = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		free(line);
		size++;
	}
	close(fd);
	return (size);
}

char	**get_map(char const *path)
{
	char	**map;
	int		fd;
	int		row;
	int		size;

	size = get_map_size(path);
	map = (char **)malloc(sizeof(char *) * (size + 1));
	if (map == NULL)
		return (ft_putstr(ERR_ALLOC_MEM), NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (free(map), ft_putstr(ERR_OPEN_FILE), NULL);
	row = -1;
	while (++row < size)
	{
		map[row] = get_map_line(fd);
		if (map[row] == NULL)
		{
			while (--row >= 0)
				free(map[row]);
			return (close(fd), free(map), ft_putstr(ERR_ALLOC_MEM), NULL);
		}
	}
	map[row] = NULL;
	return (map);
}

bool	check_file(const char *path)
{
	int		fd;
	char	*ber;

	ber = ft_strrchr(path, '.');
	if (ber != NULL && ft_strlen(ber) == 4 && !ft_strcmp(ber, ".ber"))
	{
		fd = open(path, O_RDONLY);
		if (fd != -1)
			return (true);
		else
			ft_putstr(ERR_NO_FILE);
	}
	else
		ft_putstr(ERR_EXT_UNKNOWN);
	return (false);
}

bool	parse_file(char ***map, const char *path)
{
	if (!check_file(path))
		return (false);
	*map = get_map(path);
	if (!check_map(*map))
	{
		if (*map != NULL)
			free_map(map);
		return (false);
	}
	return (true);
}
