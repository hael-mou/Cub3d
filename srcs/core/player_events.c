/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:10:04 by oezzaou           #+#    #+#             */
/*   Updated: 2023/10/15 15:01:32 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//===== move_event =============================================================
void	move(t_camera *cam, double mv_step, t_info *info, int32_t move)
{
	t_vect2d	new;
	t_vect2d	step;

	if (move == FORWARD)
		step = ft_scale_vect2d(cam->direction, mv_step);
	if (move == SIDEWAY)
		step = ft_scale_vect2d(cam->plane, mv_step);
	new = ft_add_vect2d(cam->position, step);
	if (info->map[(int)(new.y + 0.06)][(int)(new.x + 0.06)] != '0')
		return ;
	if (info->map[(int)(new.y - 0.06)][(int)(new.x - 0.06)] != '0')
		return ;
	cam->position = new;
}

//===== rotate_event ===========================================================
void	rotate(t_camera *cam, double angle)
{
	angle *= M_PI / 180;
	cam->direction = ft_rotate_vect2d(cam->direction, angle);
	cam->plane = ft_rotate_vect2d(cam->plane, angle);
}

//==== aim_event ===============================================================
void	aim(t_engine *inst)
{
	int32_t	mode;

	mode = inst->mode;
	inst->mode = ZOOM_IN * (mode == ZOOM_OUT) + ZOOM_OUT * (mode == ZOOM_IN);
	inst->info->active_anime = inst->mode;
}

//=== shoot_event ==============================================================
void	shoot(t_engine *inst)
{
	int32_t	mode;

	mode = inst->mode;
	inst->info->active_anime = SHOOT_1 * (mode == ZOOM_OUT);
	inst->info->active_anime += SHOOT_2 * (mode == ZOOM_IN);
}

// need to add reload event
