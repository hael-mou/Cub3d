/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maping_txtr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:37:04 by hael-mou          #+#    #+#             */
/*   Updated: 2023/10/12 09:47:59 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//==== render_view =============================================================
void	render_wall(t_image *view, int32_t x, t_final_ray *ray, t_info *info)
{
	int			wall_height;

	wall_height = (WIN_WIDTH / 1.4) / ray->distance;
	maping_wall_texture(view, ray, x, wall_height);
}
# include <string.h>
//==== maping_wall_texture =====================================================
uint32_t	maping_wall_texture(t_image *view, int32_t x, t_final_ray *ray, t_info *info)
{
	t_vect2d	inter_point;
	float		xp;
	int			y_max;
	int			y;

	inter_point = ft_scale_vect2d(ray->direction, ray->distance);	
	inter_point = ft_add_vect2d(ray->origin, inter_point);	
	if (ray->side == VERTICAL)
		xp = (inter_point.y) - ((int) inter_point.y);
	if (ray->side == HORIZONTAL)
		xp = (inter_point.x) - ((int) inter_point.x);
	y = ((WIN_HEIGHT - wall_h) / 2) - 1;
	y_max = y + wall_h;
	float j = y;
	while (++y < y_max)
	{
		uint32_t	color = get_texel(view, xp, (y - j) / wall_h);
		if (y >= 0 && y < WIN_HEIGHT)
			memmove(&view->pixels[y * 4 * view->width + (x * 4)], &color, 4);
	}
	return (0xff0000ff);
}

//==== get_pixel_from_texture ==================================================
uint32_t	get_texel(t_view *view, float xp, float yp)
{
	int	x;
	int	y;

	x = (xp * view->txtrs->width);
	y = (yp * view->txtrs->height);
	return (*((int *)&view->txtrs->pixels[(y * 4 * view->txtrs->width) + x * 4]));
}