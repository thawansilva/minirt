/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 16:00:03 by thaperei          #+#    #+#             */
/*   Updated: 2026/03/16 19:36:54 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_obj
{
	float	matrix[4][4];
	t_color	color;
}	t_obj;

typedef struct s_ambient
{
	float	lightness;
	t_color	color;
}	t_ambient;

typedef struct s_camera
{
	t_vec3			coordinate;
	t_vec3			norm_vector;
	unsigned char	fov;
}	t_camera;

typedef struct s_light
{
	t_vec3	coordinate;
	t_color	color;
	float	brightness;
}	t_light;

typedef struct s_sphere
{
	t_obj	obj;
	int		diameter;
}	t_sphere;

typedef struct s_plane
{
	t_obj	obj;
	t_vec3	norm_vector;
}	t_plane;

typedef struct s_cylinder
{
	t_obj	obj;
	t_vec3	norm_vector;
	float	diameter;
	float	height;
}	t_cylinder;

typedef struct s_scene
{
	t_obj			*obj;
	char			**lines;
	unsigned char	count_camera;
	unsigned char	count_ambient;
	unsigned char	count_light;
	unsigned char	count_sphere;
	unsigned char	count_plane;
	unsigned char	count_cylinder;
}	t_scene;

void	validate_input(char *file, t_scene *scene);
int		is_valid_extension(char *file);
#endif
