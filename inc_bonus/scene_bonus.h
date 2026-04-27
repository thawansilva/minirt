/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:18:18 by hermarti          #+#    #+#             */
/*   Updated: 2026/04/26 13:32:29 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_BONUS_H
# define SCENE_BONUS_H
# include "objects_bonus.h"
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
	double			brightness;
	t_color			color;
}					t_light;

typedef struct s_specular
{
	t_vec4			reflect_coordinate;
	double			strenght;
	t_color			color;
}				t_specular;

typedef struct s_scene
{
	t_camera		camera;
	t_ambient		ambient;
	t_specular		specular;
	t_list			*objs;
	t_light			*light;
	t_surface		*surfaces;
	unsigned int	idx_obj;
	unsigned int	idx_light;
	unsigned int	num_objs;
	unsigned int	num_lights;
}				t_scene;
#endif
