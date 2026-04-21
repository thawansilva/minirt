/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:18:26 by hermarti          #+#    #+#             */
/*   Updated: 2026/04/16 15:37:35 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

typedef struct s_vec4
{
	double			x;
	double			y;
	double			z;
	double			k;
}					t_vec4;

typedef struct s_mat4
{
	double			m[4][4];
}					t_mat4;

typedef struct s_ray
{
	t_vec4			dir;
	t_vec4			orig;
	double			t;
}					t_ray;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_color;

typedef struct s_obj
{
	t_vec4			coordinate;
	t_vec4			orientation;
	t_mat4			mat;
	double			min;
	double			max;
	t_color			color;
}					t_obj;

typedef enum e_surface_type
{
	SPHERE,
	PLANE,
	CYLINDER
}					t_surface_type;

typedef struct s_surface
{
	t_obj			obj;
	int				is_bounded;
	t_surface_type	type;
}					t_surface;

typedef struct s_surface_parameters
{
	t_vec4			coordinate;
	t_vec4			orientation;
	t_vec4			w;
	t_vec4			l;
	t_color			color;
	double			diameter;
	double			height;
	t_surface_type	type;
	int				is_bounded;
}					t_surface_parameters;

t_surface			create_surface(t_surface_parameters p);
t_vec4				get_surface_normal(t_surface s, t_vec4 hit_point);
#endif
