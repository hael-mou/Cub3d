/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:48:10 by hael-mou          #+#    #+#             */
/*   Updated: 2023/10/15 14:52:36 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//=====================================
void	action_handler(t_engine *inst);

//=== key_handler : ============================================================
void	key_handler(t_engine *inst)
{
	static uint16_t index;

	if (index++ % 4 == 0)
		return ;
	if (mlx_is_key_down(inst->mlx, MLX_KEY_ESCAPE))
		engine_clean(inst, EXIT_SUCCESS);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_LEFT))
		rotate(inst->cam, -4);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_RIGHT))
		rotate(inst->cam, +4);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_W))
		move(inst->cam, +0.2, inst->info, FORWARD);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_S))
		move(inst->cam, -0.2, inst->info, FORWARD);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_A))
		move(inst->cam, -0.2, inst->info, SIDEWAY);
	if (mlx_is_key_down(inst->mlx, MLX_KEY_D))
		move(inst->cam, +0.2, inst->info, SIDEWAY);
	if (inst->info->active_anime == -1)
		action_handler(inst);
}

//==================================
void	action_handler(t_engine *inst)
{
	if (mlx_is_key_down(inst->mlx, MLX_KEY_E))
		aim(inst);
	else if (mlx_is_key_down(inst->mlx, MLX_KEY_SPACE))
		shoot(inst);
	else if (mlx_is_key_down(inst->mlx, MLX_KEY_R))
	{
		inst->info->active_anime = CHARGE;
		inst->mode = ZOOM_OUT;
	}
}
