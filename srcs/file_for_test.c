/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_for_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:09:11 by hael-mou          #+#    #+#             */
/*   Updated: 2023/10/23 19:42:13 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <string.h>
//==================================================================
/*t_data	*loader(char const *file)
{
	t_data	*info;

	(void)file;
	info = ft_calloc(1, sizeof(t_data));
	info->map = ft_calloc(12, sizeof(char *));
	info->map[0] = strdup(" 11111111111111");
	info->map[1] = strdup("10000100000001 111");
	info->map[2] = strdup("1000020000000011101");
	info->map[3] = strdup("1000010001000000001");
	info->map[4] = strdup("1000010000100001111");
	info->map[5] = strdup("110011000000000111");
	info->map[6] = strdup("11210000000000011");
	info->map[7] = strdup("100000000000001");
	info->map[8] = strdup("1000000000000011");
	info->map[9] = strdup("10000000000000011");
	info->map[10] = strdup(" 11111111111111");
	info->height = 11;
	info->floor =	0xff444444;
	info->ceiling = 0xff220022;
	info->wall[NORTH] = mlx_load_png("assets/walls/music.png");
	info->wall[SOUTH] = mlx_load_png("assets/walls/music.png");
	info->wall[WEST] = mlx_load_png("assets/walls/music.png");
	info->wall[EAST] = mlx_load_png("assets/walls/music.png");
	info->door = mlx_load_png("assets/door.png");
	info->prespective = WIN_HEIGHT / 2;
	return (info);
}
*/
//==================================================================
/*t_camera	*init_camera(char **map)
{
	t_camera	*cam;

	(void)map;
	cam = ft_calloc(1, sizeof(t_camera));
	cam->position = (t_vect2d){1.5, 1.5};
	cam->direction = (t_vect2d){1, 0};
	cam->plane = (t_vect2d){0, 0.66};
	return (cam);
}*/

//=================================================================
void	load_player(t_player *player)
{
	player->mode = ZOOM_OUT;
	player->active_action = CHARGE;
	player->action[SHOOT_1].sprite = mlx_load_png("assets/guns/shoot.png");
	player->action[SHOOT_1].frame_size = 1509;
	player->action[SHOOT_1].frame = 0;

	player->action[SHOOT_2].sprite = mlx_load_png("assets/guns/shoot2.png");
	player->action[SHOOT_2].frame_size = 1509;
	player->action[SHOOT_2].frame = 0;

	player->action[ZOOM_IN].sprite = mlx_load_png("assets/guns/zoom_in.png");
	player->action[ZOOM_IN].frame_size = 1509;
	player->action[ZOOM_IN].frame = 0;

	player->action[ZOOM_OUT].sprite = mlx_load_png("assets/guns/zoom_out.png");
	player->action[ZOOM_OUT].frame_size = 1509;
	player->action[ZOOM_OUT].frame = 0;

	player->action[CHARGE].sprite = mlx_load_png("assets/guns/charge.png");
	player->action[CHARGE].frame_size = 1509;
	player->action[CHARGE].frame = 0;
}
