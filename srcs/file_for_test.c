/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_for_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:09:11 by hael-mou          #+#    #+#             */
/*   Updated: 2023/10/14 13:46:35 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
//==================================================================
t_info	*loader(char const *file)
{
	t_info	*info;

	(void)file;
	info = ft_calloc(1, sizeof(t_info));
	info->map = ft_calloc(12, sizeof(char *));
	info->map[0] = " 11111111111111";
	info->map[1] = "100000000000001 111";
	info->map[2] = "1000000000000011101";
	info->map[3] = "1000000001000000001";
	info->map[4] = "1000000000100001111";
	info->map[5] = "110010000000000111";
	info->map[6] = "10010000000000011";
	info->map[7] = "100000000000001";
	info->map[8] = "1000000000000011";
	info->map[9] = "10000000000000011";
	info->map[10] = " 11111111111111";
	info->height = 11;
	info->floor = 0x00ff0000;
	info->ceiling = 0x00ff0000;
	info->north = mlx_load_png("assets/per.png");
	info->south = mlx_load_png("assets/per.png");
	info->west = mlx_load_png("assets/per.png");
	info->east = mlx_load_png("assets/per.png");
	info->prespective = WIN_HEIGHT / 2;
	info->shoot.frame = 0;
	//info->shoot.sound = "sniper-rifle-5989.mp3";
	info->shoot.active = true;
	info->shoot.sprite = mlx_load_png("assets/shoot2.png");
	info->shoot.frame_size = 1509;
	return (info);
}

//==================================================================
t_camera	*init_camera(char **map)
{
	t_camera	*cam;

	(void)map;
	cam = ft_calloc(1, sizeof(t_camera));
	cam->position = (t_vect2d){1.5, 1.5};
	cam->direction = (t_vect2d){0, 1};
	cam->plane = (t_vect2d){-0.66, 0};
	return (cam);
}
