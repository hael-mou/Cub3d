/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:28:06 by oezzaou           #+#    #+#             */
/*   Updated: 2023/10/15 15:49:58 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

//==== mouse_cursor_handler ====================================================
void	mouse_cursor_handler(double x, double y, void *args)
{
	t_engine			*inst;

	inst = (t_engine *) args;
	mlx_set_cursor_mode(inst->mlx, MLX_MOUSE_HIDDEN);
	if (x >= 0 && x < (int) WIN_WIDTH & y >= 0 && y < (int) WIN_HEIGHT)
	{
		inst->info->perspective = WIN_HEIGHT - y;
		rotate(inst->cam, (x - (WIN_WIDTH / 2.0)) * (12.0 / WIN_WIDTH));
	}
}

//==== mouse_key_handler =======================================================
void	mouse_key_handler(mouse_key_t btn, action_t a, modifier_key_t m, void *p)
{
	(void) a;
	(void) m;
	if (btn == MLX_MOUSE_BUTTON_RIGHT)
		aim(p);
	if (btn == MLX_MOUSE_BUTTON_LEFT)
		shoot(p);
	// we can add waepon zooming
}
