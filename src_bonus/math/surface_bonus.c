/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:49:34 by hermarti          #+#    #+#             */
/*   Updated: 2026/04/16 15:38:07 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "objects_bonus.h"
#include "rt_math_bonus.h"

t_surface_parameters	set_surface_parameters(t_vec4 coordinates, t_vec4 w,
		t_vec4 l, double k)
{
	t_surface_parameters	parameters;

	ft_memset(&parameters, 0, sizeof(t_surface_parameters));
	vec4_copy(&parameters.coordinate, coordinates);
	vec4_copy(&parameters.w, w);
	vec4_copy(&parameters.l, l);
	parameters.diameter = k;
	return (parameters);
}

void	set_surface_matrix(t_surface_parameters p, t_mat4 *m)
{
	double	q44;

	m->m[0][0] = p.w.x;
	m->m[1][1] = p.w.y;
	m->m[2][2] = p.w.z;
	m->m[0][3] = -(p.w.x * p.coordinate.x) + p.l.x;
	m->m[3][0] = m->m[0][3];
	m->m[1][3] = -(p.w.y * p.coordinate.y) + p.l.y;
	m->m[3][1] = m->m[1][3];
	m->m[2][3] = -(p.w.z * p.coordinate.z) + p.l.z;
	m->m[3][2] = m->m[2][3];
	q44 = (p.w.x * p.coordinate.x * p.coordinate.x) + (p.w.y * p.coordinate.y
			* p.coordinate.y) + (p.w.z * p.coordinate.z * p.coordinate.z);
	q44 -= 2.0 * (p.l.x * p.coordinate.x + p.l.y * p.coordinate.y + p.l.z
			* p.coordinate.z);
	q44 += p.diameter;
	m->m[3][3] = q44;
}

t_surface	create_surface(t_surface_parameters p)
{
	t_surface	res;
	t_mat4		base_mat;
	t_mat4		rot_mat;
	t_mat4		rot_mat_t;
	t_vec4		default_axis;

	ft_memset(&res, 0, sizeof(res));
	ft_memset(&base_mat, 0, sizeof(t_mat4));
	set_surface_matrix(p, &base_mat);
	res.obj.coordinate = p.coordinate;
	res.obj.min = -p.height / 2;
	res.obj.max = p.height / 2;
	default_axis = (t_vec4){0.0, 1.0, 0.0, 0.0};
	rot_mat = mat4_rotation_from_to(default_axis,
			vec4_normalize(p.orientation));
	rot_mat_t = mat4_transpose(rot_mat);
	res.obj.mat = mat4_mat4_mult(mat4_mat4_mult(rot_mat, base_mat), rot_mat_t);
	res.obj.orientation = vec4_normalize(p.orientation);
	res.type = p.type;
	res.obj.color = p.color;
	return (res);
}

t_vec4	get_surface_normal(t_surface s, t_vec4 hit_point)
{
	t_vec4	n;

	ft_memset(&n, 0, sizeof(t_vec4));
	n = vec4_mat4_mul(hit_point, s.obj.mat);
	return (vec4_normalize(n));
}
