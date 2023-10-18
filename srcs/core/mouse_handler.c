/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:28:06 by oezzaou           #+#    #+#             */
/*   Updated: 2023/10/18 11:44:43 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

//==== mouse_cursor_handler ====================================================
void	mouse_cursor_handler(double x, double y, void *args)
{
	t_engine			*inst;

	(void) y;
	inst = (t_engine *) args;
	//mlx_set_cursor_mode(inst->mlx, MLX_MOUSE_HIDDEN);
//	if (x < (int) WIN_WIDTH && y < (int) WIN_HEIGHT)
//	{
	//	printf("old_x, x| %f, %f\n", inst->info->per, x);
	//	inst->info->perspective = WIN_HEIGHT - y;
		int	s = (x - inst->info->per >= 0) - (x - inst->info->per < 0);
		rotate(inst->cam, 10 * s * (1.0 - x / WIN_WIDTH));
		inst->info->per = x;
//	}
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
