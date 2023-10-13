/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:30:24 by hael-mou          #+#    #+#             */
/*   Updated: 2023/10/12 11:56:09 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//=== reycaster ================================================================
void	render_rays(t_image *view, t_image *mini, t_camera *cam, t_info *info)
{
	int32_t		screen_x;
	t_vect2d	cur;
	t_final_ray	ray;

	(void) mini;
	screen_x = -1;
	while (++screen_x < WIN_WIDTH)
	{
		cur = ft_scale_vect2d(cam->plane, (2.0 * screen_x / WIN_WIDTH) - 1.0);
		cur = ft_add_vect2d(cam->direction, cur);
		ray = raycaster(cam->position, cur, info);
		maping_textures(view, screen_x, &ray, info);
	}
}
