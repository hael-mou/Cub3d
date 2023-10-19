/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 08:45:42 by hael-mou          #+#    #+#             */
/*   Updated: 2023/10/19 07:47:10 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                                INCLUDES                                    */
/* ************************************************************************** */
# include "_define.h"
# include "_types.h"

/* ************************************************************************** */
/*                                  CORE                                      */
/* ************************************************************************** */
void		engine_clean(t_engine *inst, int exit_status);
void		engine_init(t_engine *inst);
void		engine_start(t_engine *inst);
void		key_handler(t_engine *inst);
void		rotate_camera(t_camera *cam, double angle);
void		move_camera(t_camera *cam, double mv_step, t_data *d, int32_t move);
void		mouse_key_han(mouse_key_t b, action_t a, modifier_key_t m, void *p);
void		mouse_handler(t_engine *inst);
void		animator(t_engine *engine);
void		shoot(t_engine *inst);
void		aim(t_engine *inst);

/* ************************************************************************** */
/*                                LOADER                                      */
/* ************************************************************************** */
t_data		*loader(char const *file);
t_camera	*init_camera(char **map);
void		load_player(t_player *player);

/* ************************************************************************** */
/*                               RAYCASTER                                    */
/* ************************************************************************** */
t_final_ray	raycaster(t_vect2d start, t_vect2d ray_dir, t_data *data);
void		maping_textures(mlx_image_t *v, int x, t_final_ray *r, t_data *d);
uint32_t	change_pixel_intensity(uint32_t pixel, float intensity);

/* ************************************************************************** */
/*                                SCENES                                      */
/* ************************************************************************** */
void		minimap(mlx_image_t *img, t_data *data, t_vect2d cam);
void		render_view(mlx_image_t *view, t_camera *cam, t_data *data);

#endif /* __CUB3D_H__ */
