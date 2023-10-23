/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 08:26:45 by hael-mou          #+#    #+#             */
/*   Updated: 2023/10/23 20:33:10 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//=== cub3d main : =============================================================
int	main(int number_argument, char const *argv[])
{
	t_engine	inst;

	if (number_argument == NUMBER_ARG_ALLOW)
	{
		engine_init(&inst);
		inst.data = loader(argv[1]);
		inst.cam = init_camera(inst.data->map);
		if (!inst.cam)
		{
			printf("======\n");
			clean_data(inst.data);
			return (EXIT_FAILURE);	
		}
		load_player(&inst.player);
		engine_start(&inst);
	}
	return (EXIT_SUCCESS);
}
