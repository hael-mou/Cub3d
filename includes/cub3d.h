/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 08:45:42 by hael-mou          #+#    #+#             */
/*   Updated: 2023/10/17 21:04:13 by oezzaou          ###   ########.fr       */
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

# define NORTH			0
# define SOUTH			1
# define WEST			2
# define EAST			3

# define SHOOT_1		0
# define ZOOM_IN		1
# define ZOOM_OUT		2
# define CHARGE			3
# define SHOOT_2		4

/* ************************************************************************** */
/*                                   POINT                                    */
/* ************************************************************************** */
typedef struct s_point
{
	int32_t		x;
	int32_t		y;
}	t_point;

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
/*                                    WALL                                    */
/* ************************************************************************** */
typedef struct s_wall
{
	int			height;
	int			y_min;
	int			y_max;
	float		intensity;
	t_texture	*txtr;
}				t_wall;

/* ************************************************************************** */
/*                                   action                                   */
/* ************************************************************************** */
typedef struct s_action
{
	t_texture	*sprite;
	uint32_t	frame;
	uint32_t	frame_size;
	char		*sound;
}	t_action;

/* ************************************************************************** */
/*                                    INFO                                    */
/* ************************************************************************** */
typedef struct s_info
{
	char		**map;
	int32_t		height;
	int32_t		ceiling;
	int32_t		floor;
	t_texture	*wall[4];
	t_action	anime[5];
	int32_t		perspective;
	double		per;
	int32_t		active_anime;
}	t_info;

/* ************************************************************************** */
/*                                   ENGINE                                   */
/* ************************************************************************** */
typedef struct s_engine
{
	t_mlx		*mlx;
	t_camera	*cam;
	t_info		*info;
	t_image		*view;
	t_image		*player;
	t_image		*minimap;
	int32_t		mode;
}	t_engine;

/* ************************************************************************** */
/*                                   CORE                                     */
/* ************************************************************************** */
void			engine_init(t_engine *inst);
void			engine_start(t_engine *inst);
void			engine_clean(t_engine *inst, int exit_status);
void			render(t_engine *inst);
void			key_handler(t_engine *inst);

/* ************************************************************************** */
/*                                 MINIMAP                                    */
/* ************************************************************************** */
void			minimap(t_image *img, t_info *info, t_vect2d cam);
uint32_t		get_color(t_info *info, double i, double j);

/* ************************************************************************** */
/*                               RAYCASTER                                    */
/* ************************************************************************** */
t_final_ray		raycaster(t_vect2d start, t_vect2d ray_dir, t_info *info);
t_ray			get_new_ray(t_vect2d pos, t_vect2d dir);
double			get_grid_dist(double pos, int32_t map, double dir);
void			maping_textures(t_image *view, int32_t x, t_final_ray *ray, t_info *info);

/* ************************************************************************** */
/*                                 EVENTS                                     */
/* ************************************************************************** */
void	mouse_cursor_handler(double x, double y, void *args);
void	mouse_key_handler(mouse_key_t btn, action_t a, modifier_key_t m, void *p);

void	move(t_camera *cam, double mv_step, t_info *info, int32_t move);
void	rotate(t_camera *cam, double angle);
void	aim(t_engine *inst);
void	shoot(t_engine *inst);

#endif /* __CUB3D_H__ */
