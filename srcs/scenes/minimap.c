/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:24:35 by hael-mou          #+#    #+#             */
/*   Updated: 2023/10/12 08:43:36 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//=== minimap : ================================================================
void	minimap(t_image *img, t_info *info, t_vect2d cam)
{
	double		angle;
	double		radius;
	uint32_t	color;
	t_vect2d	pnt;

	radius = 150;
	cam.x *= 25;
	cam.y *= 25;
	while (--radius)
	{
		angle = 360;
		while (angle >= 0)
		{
			pnt.x = (radius * cosf(angle * M_PI / 180));
			pnt.y = (radius * sinf(angle * M_PI / 180));
			color = get_color(info, (pnt.x + cam.x) / 25, (pnt.y + cam.y) / 25);
			mlx_pixel_put(img, pnt.x + 170, pnt.y + 170, color * (radius >= 5));
			angle -= 1.5;
		}
	}
}

//=== get_color : ==============================================================
uint32_t	get_color(t_info *info, double i, double j)
{
	if (i < 0 || j < 0 || j >= info->height)
		return (0x0098DBff);
	if (i >= ft_strlen(info->map[(int)j]))
		return (0x0098DBff);
	if (info->map[(int)j][(int)i] == '1')
		return (0xff0000ff);
	return (0xffffffff);
}
