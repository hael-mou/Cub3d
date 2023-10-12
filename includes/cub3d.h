/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 08:45:42 by hael-mou          #+#    #+#             */
/*   Updated: 2023/10/12 09:45:53 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */
# include "MLX42.h"
# include "libft.h"

/* ************************************************************************** */
/*                                  TYPEDEF                                   */
/* ************************************************************************** */
typedef struct mlx_texture		t_texture;
typedef struct mlx				t_mlx;
typedef struct mlx_image		t_image;

/* ************************************************************************** */
/*                                cub3d INFO                                  */
/* ************************************************************************** */
# define NUMBER_ARG_ALLOW   2
# define WIN_TITLE			"Cub3d"
# define WIN_WIDTH			1920
# define WIN_HEIGHT			1080

/* ************************************************************************** */
/*                                  DEFINE                                    */
/* ************************************************************************** */
# define VERTICAL		0
# define HORIZONTAL		1
# define FORWARD		1
# define SIDEWAY		2

/* ************************************************************************** */
/*                                   POINT                                    */
/* ************************************************************************** */
typedef struct s_point
{
	int32_t		x;
	int32_t		y;
}	t_point;

/* ************************************************************************** */
/*                                    INFO                                    */
/* ************************************************************************** */
typedef struct s_info
{
	char		**map;
	int32_t		height;
	int32_t		ceiling;
	int32_t		floor;
	t_texture	*north;
	t_texture	*south;
	t_texture	*west;
	t_texture	*east;
}	t_info;

/* ************************************************************************** */
/*                                   CAMERA                                   */
/* ************************************************************************** */
typedef struct s_camera
{
	t_vect2d	position;
	t_vect2d	direction;
	t_vect2d	plane;
}	t_camera;

/* ************************************************************************** */
/*                                    RAY                                     */
/* ************************************************************************** */
typedef struct s_ray
{
	t_point		pos_map;
	t_vect2d	direction;
	t_point		step;
	t_vect2d	delta;
	t_vect2d	s_dist;
}	t_ray;

typedef struct s_final_ray
{
	t_vect2d	origin;
	t_vect2d	direction;
	int32_t		side;
	double		distance;
}	t_final_ray;

/* ************************************************************************** */
/*                                   ENGINE                                   */
/* ************************************************************************** */
typedef struct s_engine
{
	t_mlx		*mlx;
	t_camera	*cam;
	t_info		*info;
	t_image		*view;
	t_image		*minimap;
}	t_engine;

/* ************************************************************************** */
/*                                   CORE                                     */
/* ************************************************************************** */
/**
 * Initialize the engine.
 * This function initializes mlx, images, and textures.. for the game.
 *
 * @param inst A pointer to the `t_engine` structure that will be initialized.
 */
void			engine_init(t_engine *inst);

/**
 * ...
 *
 * @param inst ...
 */
void			engine_start(t_engine *inst);

/**
 * Clean up and exit the engine gracefully.
 *
 * @param inst A pointer to the `t_engine` structure to clean up.
 * @param exit_status The exit status code to be returned to sys.
 */
void			engine_clean(t_engine *inst, int exit_status);

/**
 * ...
 *
 * @param inst ...
 */
void			render(t_engine *inst);

/**
 * ...
 *
 * @param inst ...
 */
void			key_handler(t_engine *inst);

/* ************************************************************************** */
/*                                 MINIMAP                                    */
/* ************************************************************************** */
/**
 * ...
 *
 * @param img ...
 * @param info ...
 * @param cam ...
 */
void			minimap(t_image *img, t_info *info, t_vect2d cam);

/**
 * ...
 *
 * @param info ...
 * @param i ...
 * @param j ...
 */
uint32_t		get_color(t_info *info, double i, double j);

#endif /* __CUB3D_H__ */

/* ************************************************************************** */
/*                               RAYCASTER                                    */
/* ************************************************************************** */

/**
 * ...
 *
 * @param start ...
 * @param ray_dir ...
 * @param info ...
 * @return ...
 */
t_final_ray		raycaster(t_vect2d start, t_vect2d ray_dir, t_info *info);

/**
 * Creates a new ray.
 * 
 * @param pos   The starting position of the ray as a 2D vector (t_vect2d).
 * @param dir   The direction of the ray as a 2D vector (t_vect2d).
 * @return      The newly created ray (t_ray) with initialized properties.
 * 
 * @note pos_map	: current position in map.
 * @note step		: move step in map.
 * @note delta		: the distance the ray has to travel
 * 					  to go from 1 side to the next side.
 * @note s_dist		: the distance the ray has to travel
 * 					  from start pos to wall for each side.
 */
t_ray			get_new_ray(t_vect2d pos, t_vect2d dir);

/**
 * Calculates distance between pos and the grid
 *
 * @param pos   current position.
 * @param map   current position in map.
 * @param dir   The direction of the calculation.
 * @return      The calculated grid distance as a double.
 */
double			get_grid_dist(double pos, int32_t map, double dir);
