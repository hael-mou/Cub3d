/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maping_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 09:39:35 by oezzaou           #+#    #+#             */
/*   Updated: 2023/10/17 15:09:02 by oezzaou          ###   ########.fr       */
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
uint32_t	change_pixel_intensity(uint32_t color, float intensity);

//		in = abs(y - wall.y_min + y - wall.y_max) / (WIN_HEIGHT * 0.3);
//		if (in > 1.0)
//			in = 1.0;
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
		float in = abs(info->perspective - y) / ((WIN_HEIGHT * 0.3) / 2.0);
		if (y < wall.y_min)
			pixel = change_pixel_intensity(info->ceiling, in);
		if (y >= wall.y_min && y < wall.y_max)
			pixel = get_texel(xp, get_yp(y, &wall), wall.txtr, wall.intensity);
		else
			pixel = change_pixel_intensity(info->floor, in);
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
	if (wall->height < WIN_HEIGHT * 0.3)
		wall->intensity = wall->height / (WIN_HEIGHT * 0.3);
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
	uint32_t	texel;

	if (!txtr)
		return (change_pixel_intensity(0xff0000ff, intensity));
	x = xp * txtr->width;
	y = yp * txtr->height;
	texel = *((int32_t *) &txtr->pixels[(y * 4 * txtr->width) + x * 4]);
	return (change_pixel_intensity(texel, intensity));
}

//==== change_pixel_intensity ==================================================
uint32_t	change_pixel_intensity(uint32_t pixel, float intensity)
{
	uint32_t	new_pixel;
	uint8_t		*byte;

	if (intensity >= 1.0)
		intensity = 1.0;
	byte = (uint8_t *) &pixel;
	new_pixel = (int) (byte[3] * intensity) << 24;
	new_pixel |= (int)(byte[2] * intensity) << 16;
	new_pixel |= (int)(byte[1] * intensity) << 8;
	new_pixel |= (int)(byte[0] * intensity);
	return (new_pixel);
}

