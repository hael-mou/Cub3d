/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:31:05 by hael-mou          #+#    #+#             */
/*   Updated: 2023/10/15 13:17:06 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//=== engine_init : ============================================================
void	engine_init(t_engine *inst)
{
	inst->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, false);
	inst->minimap = mlx_new_image(inst->mlx, WIN_WIDTH, WIN_HEIGHT);
	inst->player = mlx_new_image(inst->mlx, WIN_WIDTH, WIN_HEIGHT);
	inst->view = mlx_new_image(inst->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!inst->mlx || !inst->minimap || !inst->view || !inst->player)
		engine_clean(inst, EXIT_FAILURE);
}

//=== engine_clean : ===========================================================
void	engine_clean(t_engine *inst, int exit_status)
{
	if (inst->mlx != NULL)
	{
		mlx_delete_image(inst->mlx, inst->minimap);
		mlx_delete_image(inst->mlx, inst->player);
		mlx_delete_image(inst->mlx, inst->view);
		mlx_terminate(inst->mlx);
	}
	exit(exit_status);
}

void	animator(t_engine *inst);
//=== engine_start : ===========================================================
void	engine_start(t_engine *inst)
{
	inst->mode = ZOOM_OUT;
	mlx_image_to_window(inst->mlx, inst->view, 0, 0);
	mlx_image_to_window(inst->mlx, inst->player, 200, 0);
	mlx_image_to_window(inst->mlx, inst->minimap, 0, 0);
	mlx_loop_hook(inst->mlx, key_handler, inst);
	mlx_loop_hook(inst->mlx, render, inst);
	mlx_loop_hook(inst->mlx, animator, inst);
	mlx_cursor_hook(inst->mlx, mouse_cursor_handler, inst);
	mlx_mouse_hook(inst->mlx, mouse_key_handler, inst);
	mlx_loop(inst->mlx);
}

void	render_view(t_image *view, t_image __unused *mini, t_camera *cam, t_info *info);
//=== render function : ========================================================
void	render(t_engine *inst)
{
	static uint32_t	index;

	if (++index % 2)
		return ;
	minimap(inst->minimap, inst->info, inst->cam->position);
	render_view(inst->view, NULL, inst->cam, inst->info);
}
