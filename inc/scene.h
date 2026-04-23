/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:18:18 by hermarti          #+#    #+#             */
/*   Updated: 2026/04/01 15:05:49 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "objects.h"
# include "libft.h"

typedef struct s_ambient
{
	double			lightness;
	t_color			color;
}					t_ambient;

typedef struct s_camera
{
	t_vec4			coordinate;
	t_vec4			norm_vector;
	unsigned char	fov;
}					t_camera;

typedef struct s_light
{
	t_vec4			coordinate;
	t_color			color;
	double			brightness;
}					t_light;

typedef struct s_specular
{
	double			strenght;
	t_color			color;
	t_vec4			reflect_coordinate;
}				t_specular;

typedef struct s_scene
{
	t_list			*objs;
	t_camera		camera;
	t_ambient		ambient;
	t_light			*light;
	t_surface		*surfaces;
	t_specular		specular;
	unsigned int	idx_obj;
	unsigned int	num_objs;
	unsigned int	num_lights;
}				t_scene;
#endif
