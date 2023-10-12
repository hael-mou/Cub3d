/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:48:10 by hael-mou          #+#    #+#             */
/*   Updated: 2023/10/12 08:32:09 by hael-mou         ###   ########.fr       */
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

//=== key_handler : ============================================================
void	key_handler(t_engine *inst)
{
	if (mlx_is_key_down(inst->mlx, MLX_KEY_ESCAPE))
		engine_clean(inst, EXIT_SUCCESS);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_LEFT))
		rotate_camera(inst->cam, -4);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_RIGHT))
		rotate_camera(inst->cam, +4);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_W))
		move_camera(inst->cam, +0.06, inst->info, FORWARD);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_S))
		move_camera(inst->cam, -0.06, inst->info, FORWARD);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_A))
		move_camera(inst->cam, -0.06, inst->info, SIDEWAY);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_D))
		move_camera(inst->cam, +0.06, inst->info, SIDEWAY);
}
