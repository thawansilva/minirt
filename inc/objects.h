/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:18:26 by hermarti          #+#    #+#             */
/*   Updated: 2026/04/01 15:08:59 by hermarti         ###   ########.fr       */
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
	double			mat[4][4];
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
	t_surface_type	type;
}					t_surface;

typedef struct s_surface_parameters
{
	t_vec4			c;
	t_vec4			w;
	t_vec4			l;
	double			k;
}					t_surface_parameters;

t_surface			create_surface(t_surface_parameters p);
t_vec4				get_surface_normal(t_surface s, t_vec4 hit_point);
#endif
