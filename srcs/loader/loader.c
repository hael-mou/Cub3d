/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:54:27 by oezzaou           #+#    #+#             */
/*   Updated: 2023/10/24 00:58:01 by oezzaou          ###   ########.fr       */
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

//====< check_map >=============================================================
static int	check_map(char **map, t_data *data)
{
	int		row;
	int		colum;

	row = 0;
	while (row < 4 && data->wall[row])
		row++;
	if (row < 4)
		return (ft_perror("Invalid Textures"), false);
	if (data->floor <= 1 || data->ceiling <= 1)
	   return (ft_perror("Invalid color"), false);
	row = -1;	
	while (map[++row])
	{
		colum = -1;
		while (map[row][++colum])
		{
			if (!strchr(" 1", map[row][colum]) && !check_unit(map, row, colum))
				return (false);
		}
	}
	data->height = row;
	return (true);
}

int	load_assets(char *line, t_data *data);
//===< loader >=================================================================
t_data	*loader(char const *file)
{
	t_data	*data;
	int		fd;
	char	*line;
	
	data = ft_calloc(1, sizeof(t_data));
	fd = open(file, O_RDONLY);
	if (data == NULL || fd < 0)
		return (free(data), close(fd), NULL);
	data->prespective = WIN_HEIGHT / 2;
	line = get_line(fd, 0);
	while (is_map(line) == false)
	{
		if (*line && load_assets(line, data) == false)
			return (free(line), clean_data(data));
		free(line);
		line = get_line(fd, 0);
	}
	data->map = read_map(fd, line, 0);
	if (check_map(data->map, data) == false)
		return (clean_data(data), NULL);
	return (data);
}
size_t	get_color(char *line);
t_token	tokenizer(char *line);
//====< load_assets >===========================================================
int	load_assets(char *line, t_data *data)
{
	char	**dir;
	t_token token;
	int		index;

	index = -1;
	dir = (char *[4]) {"NO", "SO", "WE", "EA"};
	token = tokenizer(line);
	while (++index < 4)
	{
		if (ft_strcmp(dir[index], token.key) == 0)
		{
			data->wall[index] = mlx_load_png(token.value);
			if (!data->wall[index])
				return (false);
			return (true);
		}
	}
	if (ft_strcmp("F", token.key) == 0 && data->floor == 0)
	{
		data->floor = get_color(token.value);
		return (true);
	}	
	if (ft_strcmp("C", token.key) == 0 && data->ceiling == 0)
	{
		data->ceiling = get_color(token.value);
		return (true);	
	}
	return (false);
}

void	set_camera(t_camera *cam, int x, int y, char *dir);
//=== init_camera : ============================================================
t_camera	*init_camera(char **map)
{
	t_camera	*cam;
	int			x;
	int			y;

	y = -1;
	cam = ft_calloc(1, sizeof(t_camera));
	if (cam == NULL || map == NULL)
		return (free(cam), NULL);
	cam->position = (t_vect2d){-1, -1};
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (strchr("NSEW", map[y][x]))
			{
				if (cam->position.x != -1)
					return (free(cam), NULL);
				set_camera(cam, x, y, &map[y][x]);
			}
		}
	}
	if (cam->position.x == -1)
		return (free(cam), NULL);
	return (cam);
}

//====< set_camera >============================================================
void	set_camera(t_camera *cam, int x, int y, char *dir)
{
	cam->position = (t_vect2d){x + 0.5, y + 0.5};
	if (*dir == 'N')
	{
		cam->direction = (t_vect2d){0, -1};
		cam->plane = (t_vect2d){0.66, 0};
	}
	else if (*dir == 'S')
	{
		cam->direction = (t_vect2d){0, 1};
		cam->plane = (t_vect2d){-0.66, 0};
	}
	else if (*dir == 'W')
	{
		cam->direction = (t_vect2d){-1, 0};
		cam->plane = (t_vect2d){0, -0.66};
	}
	else if (*dir == 'E')
	{
		cam->direction = (t_vect2d){1, 0};
		cam->plane = (t_vect2d){0, 0.66};
	}
	*dir = '0';
}
