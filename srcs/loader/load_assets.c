/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:40:18 by hael-mou          #+#    #+#             */
/*   Updated: 2023/10/24 16:01:03 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//====< get_color >=============================================================
static uint32_t	get_color(char *line)
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

//====< load_texture >==========================================================
static int	load_texture(t_token token, t_data *data)
{
	char	**dir;
	int		index;

	index = -1;
	dir = (char *[4]){"NO", "SO", "WE", "EA"};
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
	return (false);
}

//====< load_ceiling_floor >====================================================
static int	load_ceiling_floor(t_token token, t_data *data)
{
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

//====< load_assets >===========================================================
int	load_assets(char *line, t_data *data)
{
	t_token	token;

	token = tokenizer(line);
	if (load_texture(token, data) == true)
		return (true);
	if (load_ceiling_floor(token, data) == true)
		return (true);
	return (false);
}
