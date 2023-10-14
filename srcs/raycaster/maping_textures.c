/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maping_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:38:25 by oezzaou           #+#    #+#             */
/*   Updated: 2023/10/14 14:38:36 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>
#include <stdio.h>

//==============================================================================
float		get_xp(t_final_ray *ray);
float		get_yp(int32_t y, t_wall *wall);
uint32_t	get_texel(float xp, float yp, t_texture *txtr);
void		get_wall_info(t_wall *wall, t_final_ray *ray, t_info *info);

//==== maping_textures =========================================================
void	maping_textures(t_image *view, int32_t x, t_final_ray *ray, t_info *info)
{
	t_wall		wall;
	uint32_t	pixel;
	float		xp;
	int32_t		y;

	get_wall_info(&wall, ray, info);
	xp = get_xp(ray);
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		if (y < wall.y_min)
			pixel = info->ceiling;
		else if (y >= wall.y_min && y < wall.y_max)
			pixel = get_texel(xp, get_yp(y, &wall), wall.txtr);
		else
			pixel = info->floor;
		memmove(&view->pixels[y * 4 * view->width + (x * 4)], &pixel, 4);
	}
}

//==== get_wall_info ===========================================================
void	get_wall_info(t_wall *wall, t_final_ray *ray, t_info *info)
{
	wall->height = WIN_WIDTH / 1.4 / ray->distance;
	wall->y_min = info->prespective - (wall->height / 2);
	wall->y_max = wall->y_min + wall->height;
	if (ray->side == VERTICAL && ray->direction.x > 0)
		wall->txtr = info->wall[NORTH];
	if (ray->side == VERTICAL && ray->direction.x < 0)
		wall->txtr = info->wall[SOUTH];
	if (ray->side == HORIZONTAL && ray->direction.y < 0)
		wall->txtr = info->wall[EAST];
	if (ray->side == HORIZONTAL && ray->direction.y > 0)
		wall->txtr = info->wall[WEST];
}

//==== get_yp ==================================================================
float	get_yp(int32_t y, t_wall *wall)
{
	return ((y - wall->y_min) / (float) wall->height);
}

//==== get_xp ==================================================================
float	get_xp(t_final_ray *ray)
{
	t_vect2d	ipv;
	float		xp;
	
	ipv = ft_scale_vect2d(ray->direction, ray->distance);	
	ipv = ft_add_vect2d(ray->origin, ipv);
	if (ray->side == HORIZONTAL)
		xp = (ray->direction.y > 0) - (ipv.x - (int) ipv.x);
	if (ray->side == VERTICAL)
		xp = (ray->direction.x < 0) - (ipv.y - (int) ipv.y);
	return (fabs(xp));
}

//==== get_texel ===============================================================
uint32_t	get_texel(float xp, float yp, t_texture *txtr)
{
	int	x;
	int	y;

	// Add color to each side
	if (!txtr)
		return (0xff0000ff);
	x = xp * txtr->width;
	y = yp * txtr->height;
	return (*((int *)&txtr->pixels[(y * 4 * txtr->width) + x * 4]));
}
