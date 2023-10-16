/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_for_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:09:11 by hael-mou          #+#    #+#             */
/*   Updated: 2023/10/16 12:52:23 by oezzaou          ###   ########.fr       */
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
	info->map[1] = "100000000000010111";
	info->map[2] = "1000000101000011101";
	info->map[3] = "1000000101000000001";
	info->map[4] = "1000000101100001111";
	info->map[5] = "110010010100000111";
	info->map[6] = "10010001010000011";
	info->map[7] = "100000010100001";
	info->map[8] = "10000001010000011";
	info->map[9] = "10000001010000011";
	info->map[10] = " 11111111111111";
	info->height = 11;
	info->floor = 0x00ff0000;
	info->ceiling = 0x00ff0000;
	info->wall[NORTH]= mlx_load_png("assets/walls/per.png");
	info->wall[SOUTH]= mlx_load_png("assets/walls/per.png");
	info->wall[WEST]= mlx_load_png("assets/walls/per.png");
	info->wall[EAST]= mlx_load_png("assets/walls/per.png");
	info->perspective = WIN_HEIGHT / 2;
	//init animation :
	info->active_anime = CHARGE;
	info->anime[SHOOT_1].frame = 0;
	info->anime[SHOOT_1].sound = "sniper-rifle-5989.mp3";
	info->anime[SHOOT_1].sprite = mlx_load_png("assets/guns/shoot.png");
	info->anime[SHOOT_1].frame_size = 1509;
	
	info->anime[SHOOT_2].frame = 0;
	info->anime[SHOOT_2].sound = "sniper-rifle-5989.mp3";
	info->anime[SHOOT_2].sprite = mlx_load_png("assets/guns/shoot2.png");
	info->anime[SHOOT_2].frame_size = 1509;

	info->anime[ZOOM_IN].frame = 0;
	info->anime[ZOOM_IN].sound = "sniper-rifle-5989.mp3";
	info->anime[ZOOM_IN].sprite = mlx_load_png("assets/guns/zoom_in.png");
	info->anime[ZOOM_IN].frame_size = 1509;

	info->anime[ZOOM_OUT].frame = 0;
	info->anime[ZOOM_OUT].sound = "sniper-rifle-5989.mp3";
	info->anime[ZOOM_OUT].sprite = mlx_load_png("assets/guns/zoom_out.png");
	info->anime[ZOOM_OUT].frame_size = 1509;

	info->anime[CHARGE].frame = 0;
	info->anime[CHARGE].sound = "sniper-rifle-5989.mp3";
	info->anime[CHARGE].sprite = mlx_load_png("assets/guns/charge.png");
	info->anime[CHARGE].frame_size = 1509;
	return (info);
}

//==================================================================
t_camera	*init_camera(char **map)
{
	t_camera	*cam;

	(void)map;
	cam = ft_calloc(1, sizeof(t_camera));
	cam->position = (t_vect2d){1.5, 1.5};
	cam->direction = (t_vect2d){-1, 0};
	cam->plane = (t_vect2d){0, -0.66};
	return (cam);
}
