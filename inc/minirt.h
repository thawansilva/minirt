/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 16:00:03 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/27 09:50:53 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "scene.h"

typedef struct s_img_buffer
{
	void			*img;
	char			*img_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_img_buffer;

typedef struct s_window
{
	int				width;
	int				height;
	void			*mlx;
	void			*x_window;
	t_img_buffer	img;
}					t_window;

typedef struct s_env
{
	t_window	window;
	t_scene		scene;
}				t_env;

void				*init_env(t_env *env, int argc, char **argv);
void				*destroy_env(t_env *env);

void				*init_window(t_window *window, int width, int height, char *window_name);
void				*destroy_window(t_window *window);
int					close_window(t_env *env);

int					mouse_handler(int mousecode, int x, int y, t_env *env);
int					key_handler(int keycode, t_env *env);

void				*init_img_buffer(t_window *window);
void				*destroy_img_buffer(t_window *window);

#endif
