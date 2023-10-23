/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:54:27 by oezzaou           #+#    #+#             */
/*   Updated: 2023/10/23 17:10:42 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//====< read_map >==============================================================
static char	**read_map(int fd, char *line, int index)
{
	char	**map;
	char	*cur_line;

	cur_line = get_line(fd, 0);
	if (line == NULL)
		return (ft_calloc((index + 1) * !!index, sizeof(char *)));
	map = read_map(fd, cur_line, index + 1);
	if (!map)
		return (free(line), NULL);
	map[index] = line;
	return (map);
}

//=== loader : ================================================================
t_data	*loader(char const *file)
{
	t_data	*data;
	int		fd;
	char	*line;
	
	data = ft_calloc(1, sizeof(t_data));
	fd = open(file, O_RDONLY);
	if (data == NULL || fd < 0)
		return (free(data), close(fd), NULL);
	line = get_line(fd, 0);
	while (is_map(line) == false)
	{
//		if (load_assets(line, data) == false)
//			return (free(line), clean_data(data));
		free(line);
		line = get_line(fd, 0);
	}
	data->map = read_map(fd, line, 0);
	int	i = -1;
	while (data->map[++i])
		printf("MAP| %s\n", (data->map)[i]);
//	if (check_map(data->map) == false)
//		return (clean_data(data), NULL);
	return (data);
}
