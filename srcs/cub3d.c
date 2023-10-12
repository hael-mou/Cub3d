/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 08:26:45 by hael-mou          #+#    #+#             */
/*   Updated: 2023/10/11 11:14:59 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//for test:
t_info		*loader(char const *file);
t_camera	*init_camera(char **map);

//=== cub3d main : =============================================================
int	main(int argc, char const __unused *argv[])
{
	t_engine	engine;

	if (argc == NUMBER_ARG_ALLOW)
	{
		engine_init(&engine);
		engine.info = loader(argv[1]);
		engine.cam = init_camera(engine.info->map);
		engine_start(&engine);
	}
	return (EXIT_FAILURE);
}
