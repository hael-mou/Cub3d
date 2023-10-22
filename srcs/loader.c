/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:54:27 by oezzaou           #+#    #+#             */
/*   Updated: 2023/10/22 17:35:05 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#define	MAP	0
#define OTHER	1

//==============================================================================
void		*ft_calloc(size_t count, size_t size);
char		*get_next_line(int fd, int index);
uint32_t	extract_rgb_color(char *line);
//==============================================================================
//==============================================================================
t_data	*loader(char const *file);
char	**parse_scene_file(int fd, int index, int area);
//==============================================================================
int	check_map_line(char *colom, int *area);
int	check_texture(char *line, int *area);
int	analize_line(char *line, int *area);
int	check_ceiling_floor_line(char *line, int *area);

//==============================================================================
int	load_textures(char **lines, t_data *data);
int	load_ceiling_floor_color(char **lines, t_data *data);
int	load_map(char **lines, t_data *data);

//==============================================================================
t_data	*loader(char const *file)
{
	t_data	*data;
	char	**lines;
	int		fd;
	int		re;

	data = (t_data *) malloc(sizeof(t_data));
	fd = open(file, O_RDONLY);
	if (!data || fd < 0)
		return (free(data), NULL);
	lines = parse_scene_file(fd, 0, OTHER);
	if (!lines)
		return (free(data), printf("error\n"), NULL);
//	re = load_textures(lines, data);
	re = 1;
	re += load_ceiling_floor_color(lines, data);
	re += load_map(lines, data);
	printf("CEILING| => %u\n", data->ceiling);
	printf("FLOOR| => %u\n", data->floor);
	if (re != 3)
	   return (free(data), free(lines), NULL);
	return (data);
}

int	load_map(char **lines, t_data *data)
{
	(void) lines;
	(void) data;
	return (1);
}

//==== load_ceiling_floor_color ================================================
int	load_ceiling_floor_color(char **lines, t_data *data)
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
	return (data->floor >= 0 && data->ceiling >= 0 && var[0] + var[1] == 2);
}

//==== load_textures ===========================================================
int	load_textures(char **lines, t_data *data)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (lines[++i])
	{
		if (strstr(lines[i], "NO") && ++count)
			data->wall[0] = mlx_load_png(strchr(lines[i], '/') + 1);
		if (strstr(lines[i], "SO") && ++count)
			data->wall[1] = mlx_load_png(strchr(lines[i], '/') + 1);
		if (strstr(lines[i], "WE") && ++count)
			data->wall[2] = mlx_load_png(strchr(lines[i], '/') + 1);
		if (strstr(lines[i], "EA") && ++count)
			data->wall[3] = mlx_load_png(strchr(lines[i], '/') + 1);
		// IF one of these NULL error loding
	}
	return (count == 4);
}

//==== parse_===================================================================
char	**parse_scene_file(int fd, int index, int area)
{
	char	**lines;
	char	*line;

	line = get_next_line(fd, 0);
	if (!line || !analize_line(line, &area))
		return (ft_calloc((index + 1) * (!line && area == MAP), sizeof(char *)));
	lines = parse_scene_file(fd, index + 1, area);
	if (!lines)
		return (free(line), NULL);
	lines[index] = line;
	return (lines);
}

//==== line_analyser ===========================================================
int	analize_line(char *line, int *area)
{
	if (!line || (line && !*line && *area != MAP))
		return (1);
	else if (strstr(line, "NO") || strstr(line, "SO")
		|| strstr(line, "WE") || strstr(line, "EA"))
		return (check_texture(line, area));
	else if (strstr(line, "F") || strstr(line, "C"))
		return (check_ceiling_floor_line(line, area));
	else
		*area = MAP;
	return (*line || *area != MAP);
}

//=== check_ceiling_floor_line ==================================================
int	check_ceiling_floor_line(char *line, int *area)
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
}

//==== check_texture ===========================================================
int	check_texture(char *line, int *area)
{
	char	*tmp;

	if (*area != OTHER)
		return (0);
	tmp = strchr(line, '/');
	if (tmp && access(tmp + 1, F_OK | R_OK) == 0)
		return (1);
	return (0);
}