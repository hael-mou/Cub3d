/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:54:27 by oezzaou           #+#    #+#             */
/*   Updated: 2023/10/23 20:42:10 by oezzaou          ###   ########.fr       */
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
	line = get_line(fd, 0);
	while (is_map(line) == false)
	{
//		if (load_assets(line, data) == false)
//			return (free(line), clean_data(data));
		free(line);
		line = get_line(fd, 0);
	}
	data->map = read_map(fd, line, 0);
	if (check_map(data->map, data) == false)
		return (clean_data(data), NULL);
	return (data);
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
	else if (*dir == 'E')
	{
		cam->direction = (t_vect2d){-1, 0};
		cam->plane = (t_vect2d){0, -0.66};
	}
	else if (*dir == 'W')
	{
		cam->direction = (t_vect2d){1, 0};
		cam->plane = (t_vect2d){0, 0.66};
	}
	*dir = '0';
}
