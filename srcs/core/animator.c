/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 08:54:27 by hael-mou          #+#    #+#             */
/*   Updated: 2023/10/14 16:48:18 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>
#include <stdio.h>
void	play_animation(t_image *img, t_action *action, int32_t *active_anime);
//===
void	animator(t_engine *inst)
{
	static uint16_t	index;
	t_action		*anime;
	
	if (index++ % 2 == 0 && inst->info->active_anime != -1)
	{
		anime = &inst->info->anime[inst->info->active_anime];
		play_animation(inst->player, anime, &inst->info->active_anime);
	}
}

//===
void	play_animation(t_image *img, t_action *action, int32_t *active_anime)
{
	uint32_t	img_y;
	uint32_t	width;
	uint8_t		*pexels;

	img_y = -1;
	width = action->sprite->width - action->frame;
	width = width * (width <= img->width) + img->width * (img->width < width);
	if (action->frame >= action->sprite->width)
	{
		action->frame = 0;
		*active_anime = -1;
		return ;
	}
	while (++img_y < img->height && img_y < action->sprite->height)
	{
		pexels = action->sprite->pixels;
		pexels += (img_y * action->sprite->width + action->frame) * 4;
		memmove(&img->pixels[img_y * img->width * 4], pexels, width * 4);
	}
	action->frame += action->frame_size;
}