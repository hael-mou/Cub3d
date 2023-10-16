/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maping_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 09:39:35 by oezzaou           #+#    #+#             */
/*   Updated: 2023/10/16 12:51:56 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"
#include <string.h>
#include <stdio.h>

//==============================================================================
float		get_xp(t_final_ray *ray);
float		get_yp(int32_t y, t_wall *wall);
uint32_t	get_texel(float xp, float yp, t_texture *txtr, float intensity);
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
			pixel = get_texel(xp, get_yp(y, &wall), wall.txtr, wall.intensity);
		else
			pixel = info->floor;
		memmove(&view->pixels[y * 4 * view->width + (x * 4)], &pixel, 4);
	}
}

//==== get_wall_info ===========================================================
void	get_wall_info(t_wall *wall, t_final_ray *ray, t_info *info)
{
	wall->height = WIN_WIDTH / (1.4 * ray->distance);
	wall->y_min = info->perspective - (wall->height / 2);
	wall->y_max = wall->y_min + wall->height;
	wall->intensity = 1.0;
	if (wall->height < (WIN_HEIGHT * 0.30))
		wall->intensity = wall->height / (WIN_HEIGHT * 0.30);
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
uint32_t	get_texel(float xp, float yp, t_texture *txtr, float intensity)
{
	int			x;
	int			y;
	uint8_t		*tmp;
	int			texel;

	if (!txtr)
		return (0xff0000ff);
	x = xp * txtr->width;
	y = yp * txtr->height;
	tmp = &txtr->pixels[(y * 4 * txtr->width) + x * 4];
	texel =	(int)(tmp[3] * intensity) << 24;
	texel |= (int)(tmp[2] * intensity) << 16;
	texel |= (int)(tmp[1] * intensity) << 8;
	texel |= (int)(tmp[0] * intensity);
	return (texel);
}
