/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:48:10 by hael-mou          #+#    #+#             */
/*   Updated: 2023/10/14 17:39:35 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//==== rotate_camera ===========================================================
void	rotate_camera(t_camera *cam, double angle)
{
	angle *= M_PI / 180;
	cam->direction = ft_rotate_vect2d(cam->direction, angle);
	cam->plane = ft_rotate_vect2d(cam->plane, angle);
}

//==== move_camera =============================================================
void	move_camera(t_camera *cam, double mv_step, t_info *info, int32_t move)
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

//===
void	action_handler(t_engine *inst)
{
	if (mlx_is_key_down(inst->mlx, MLX_KEY_E) && inst->mode == ZOOM_OUT)
	{	
		inst->info->active_anime = ZOOM_IN;
		inst->mode = ZOOM_IN;
	}
	else if (mlx_is_key_down(inst->mlx, MLX_KEY_E) && inst->mode == ZOOM_IN)
	{
		inst->info->active_anime = ZOOM_OUT;
		inst->mode = ZOOM_OUT;
	}
	else if (mlx_is_key_down(inst->mlx, MLX_KEY_SPACE) && inst->mode == ZOOM_OUT)
		inst->info->active_anime = SHOOT_1;
	else if (mlx_is_key_down(inst->mlx, MLX_KEY_SPACE) && inst->mode == ZOOM_IN)
		inst->info->active_anime = SHOOT_2;
	else if (mlx_is_key_down(inst->mlx, MLX_KEY_R))
	{
		inst->info->active_anime = CHARGE;
		inst->mode = ZOOM_OUT;
	}
}

//=== key_handler : ============================================================
void	key_handler(t_engine *inst)
{
	static uint16_t index;

	if (index++ % 4 == 0)
		return ;
	if (mlx_is_key_down(inst->mlx, MLX_KEY_ESCAPE))
		engine_clean(inst, EXIT_SUCCESS);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_LEFT))
		rotate_camera(inst->cam, -4);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_RIGHT))
		rotate_camera(inst->cam, +4);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_W))
		move_camera(inst->cam, +0.2, inst->info, FORWARD);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_S))
		move_camera(inst->cam, -0.2, inst->info, FORWARD);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_A))
		move_camera(inst->cam, -0.2, inst->info, SIDEWAY);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_D))
		move_camera(inst->cam, +0.2, inst->info, SIDEWAY);
	if (inst->info->active_anime == -1)
		action_handler(inst);
}
