/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maping_txtr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:38:25 by oezzaou           #+#    #+#             */
/*   Updated: 2023/10/12 11:06:25 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

uint32_t	maping_wall_texture(t_image *view, int32_t x, t_final_ray *ray, t_info *info);
uint32_t	get_texel(float xp , float yp, t_info *info);

//==== maping_wall_texture =====================================================
uint32_t	maping_wall_texture(t_image *view, int32_t x, t_final_ray *ray, t_info *info)
{
	t_vect2d	inter_point;
	float		xp;
	int			y_max;
	int			y;
	int			wall_h;
	
	wall_h = (WIN_WIDTH / 1.4) / ray->distance;
	inter_point = ft_scale_vect2d(ray->direction, ray->distance);	
	inter_point = ft_add_vect2d(ray->origin, inter_point);	
	if (ray->side == VERTICAL)
		xp = (inter_point.y) - ((int) inter_point.y);
	if (ray->side == HORIZONTAL)
		xp = (inter_point.x) - ((int) inter_point.x);
	y = ((WIN_HEIGHT - wall_h) / 2) - 1;
	y_max = y + wall_h;
	(void) info;
	//	float j = y;
	while (++y < y_max)
	{
//		uint32_t	color = get_texel(xp, (y - j) / wall_h, info);
//		if (y >= 0 && y < WIN_HEIGHT)
			mlx_pixel_put(view, x, y, 0xff0000ff);
//		if (y >= 0 && y < WIN_HEIGHT)
//			memmove(&view->pixels[y * 4 * view->width + (x * 4)], &color, 4);
	}
	return (0xff0000ff);
}

//==== get_pixel_from_texture ==================================================
uint32_t	get_texel(float xp, float yp, t_info *info)
{
	int	x;
	int	y;

	x = (xp * info->north->width);
	y = (yp * info->north->height);
	return (*((int *)&info->north->pixels[(y * 4 * info->north->width) + x * 4]));
}
