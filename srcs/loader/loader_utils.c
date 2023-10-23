/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:16:52 by oezzaou           #+#    #+#             */
/*   Updated: 2023/10/24 00:55:12 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//====< get_line >==============================================================
char	*get_line(int fd, int index)
{
	char	*tmp;
	char	c;

	if (!read(fd, &c, 1) || c == '\n')
		return (ft_calloc((index + 1) * !(!index && c != '\n'), 1));
	tmp = get_line(fd, index + 1);
	if (tmp)
		tmp[index] = c;
	return (tmp);
}

//====< check_space >===========================================================
int	check_unit(char **map, int row, int colum)
{
	if (!strchr(" 012NSWE", map[row][colum]))
		return (false);
	if (!row || !colum || !map[row + 1] || !map[row][colum + 1])
		return (false);
	else if (map[row][colum - 1] == ' ' || map[row][colum + 1] == ' ')
		return (false);
	else if (ft_strlen(map[row - 1]) < colum + 1
			|| ft_strlen(map[row + 1]) < colum + 1)
		return (false);
	else if (map[row - 1][colum] == ' ' || map[row + 1][colum] == ' ')
		return (false);
	return (true);
}

//====< is_map >================================================================
int	is_map(char *line)
{
	int	index;

	index = 0;
	if (line == NULL)
		return (true);
	while (line[index] && strchr(" 012NSEW", line[index]))
		index++;
	return (index && line[index] == '\0');
}

//====< get_color >==============================================================
uint32_t get_color(char *line)
{
	int	rgb[3];
	int	i;

	i = -1;
	while (*line && ++i < 3)
	{
		if (*line == ',')
			return (1);
		rgb[i] = atoi(line);
		while (*line && *line != ',')
		{
			if (*line < '0' || *line > '9' || rgb[i] > 255)
				return (1);
			line++;
		}
		line += (*line == ',' && i < 3);
	}
	if (*line)
		return (1);
	return (255 << 24 | rgb[2] << 16 | rgb[1] << 8 | rgb[0]);
}

//====< clean_data >=============================================================
void	*clean_data(t_data *data)
{
	int	i;

	i = -1;
	if (data == NULL)
		return (NULL);
	while (++i < 4)
	{
		if (data->wall[i])
			mlx_delete_texture(data->wall[i]);
	}
	i = -1;
	while (data->map && data->map[++i])
		free(data->map[i]);
	free(data->map);
	return (NULL);
}
