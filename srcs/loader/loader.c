/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:54:27 by oezzaou           #+#    #+#             */
/*   Updated: 2023/10/23 15:58:28 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#define	MAP	0
#define OTHER	1

//==============================================================================
char	*get_line(int fd, int index);

//==============================================================================
t_data	*loader(char const *file);
char	**read_map(int fd, char *line, int index);

//==============================================================================
int	load_map(char **lines, t_data *data);

//==============================================================================
t_data	*loader(char const *file)
{
	t_data	*data;
	int		fd;
//	char	*line;
	
	data = ft_calloc(1, sizeof(t_data));
	fd = open(file, O_RDONLY);
	if (data == NULL || fd < 0)
		return (free(data), close(fd), NULL);
//	while (true)
//	{
//		line = get_line(fd, 0);
//		if (is_map(line) == true)
//			break ;
//		if (load_assets(line, data) == false)
//			return (free(line), clean_data(data)); 
//		free(line);
//	}
	data->map = read_map(fd, NULL, 0);
//	if (check_map(data->map) == false)
//		return (clean_data(data), NULL);
	return (data);
}

int	load_map(char **lines, t_data *data)
{
	int		i;
	int		j;

	(void) data;
	i = -1;
	while (lines[++i])
	{
		j = -1;
		while (lines[i][++j])
		{
			if (!strchr(" 012NSWE", lines[i][j]))
				return (0);
			if (lines[i][j] != '0')
				continue ;
			if (!j || !i || !lines[i][j + 1] || !lines[i + 1])
				return (0);
			else if (lines[i][j - 1] == ' ' || lines[i][j + 1] == ' ')
				return (0);
			else if (ft_strlen(lines[i - 1]) < j + 1
					|| ft_strlen(lines[i + 1]) < j + 1)
				return (0);
			else if (lines[i - 1][j] == ' ' || lines[i + 1][j] == ' ')
				return (0);
		}
	}
	return (1);
}

//====< read_map >==============================================================
char	**read_map(int fd, char *line, int index)
{
	char	**map;
	char	*cur_line;

	cur_line = get_line(fd, 0);
	if (!line)
	{
		map = ft_calloc(index + 1, sizeof(char *));
		map[index] = line;
		return (map);
	}
	map = read_map(fd, cur_line, index + 1);
	if (!map)
		return (free(line), NULL);
	map[index] = line;
	return (map);
}

//==== load_ceiling_floor_color ================================================
/*int	load_ceiling_floor_color(char **lines, t_data *data)
{
	int32_t	*var;

	var = (int [2]){0, 0};
	while (*lines)
	{
		if (strchr(*lines, 'C') && ++var[0])
			data->ceiling = extract_rgb_color(*lines);
		if (strchr(*lines, 'F') && ++var[1])
			data->floor = extract_rgb_color(*lines);
		lines++;
	}
	return (data->floor >= 0 && data->ceiling >= 0 && var[0] == 1 && var[1] == 1);
}*/

//=== check_ceiling_floor_line ==================================================
/*int	check_ceiling_floor_line(char *line, int *area)
{
	int	prev_state;
	int	count;

	if (*area != OTHER)
		return (0);
	count = 0;
	prev_state = *line;
	while (*line)
	{
		if (prev_state == ',' && *line == ',')
			return (0);
		if (prev_state != ',' && *line == ',')
			count++;
		prev_state = *(line++);
	}
	return (count == 2);
}*/

//==== load_textures ===========================================================
/*int	load_textures(char *line, t_data *data)
{
	char	*dir[4];
	int		i;

	dir[0] = "NO";
	dir[1] = "SO";
	dir[2] = "EA";
	dir[3] = "WE";
	i = -1;
	while (++i < 4)
	{
		if (strstr(line, dir[i]) && !data->wall[i])
		{
			data->wall[i] = load_png(ft_strchr(line, '/') + 1);
			if (!data->wall[i])
				return (0);
		}
	}
	return (1);
}*/
