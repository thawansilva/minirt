/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:49:34 by hermarti          #+#    #+#             */
/*   Updated: 2026/04/08 16:19:41 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "objects.h"
#include "rt_math.h"

t_surface_parameters	set_surface_parameters(t_vec4 c, t_vec4 w, t_vec4 l,
		double k)
{
	t_surface_parameters	parameters;

	ft_memset(&parameters, 0, sizeof(t_surface_parameters));
	vec4_copy(&parameters.c, c);
	vec4_copy(&parameters.w, w);
	vec4_copy(&parameters.l, l);
	parameters.k = k;
	return (parameters);
}

t_surface	create_surface(t_surface_parameters p)
{
	t_surface	res;
	double		q44;

	ft_memset(&res, 0, sizeof(res));
	res.obj.mat[0][0] = p.w.x;
	res.obj.mat[1][1] = p.w.y;
	res.obj.mat[2][2] = p.w.z;
	res.obj.mat[0][3] = -(p.w.x * p.c.x) + p.l.x;
	res.obj.mat[3][0] = res.obj.mat[0][3];
	res.obj.mat[1][3] = -(p.w.y * p.c.y) + p.l.y;
	res.obj.mat[3][1] = res.obj.mat[1][3];
	res.obj.mat[2][3] = -(p.w.z * p.c.z) + p.l.z;
	res.obj.mat[3][2] = res.obj.mat[2][3];
	q44 = (p.w.x * p.c.x * p.c.x) + (p.w.y * p.c.y * p.c.y) + (p.w.z * p.c.z
			* p.c.z);
	q44 -= 2.0 * (p.l.x * p.c.x + p.l.y * p.c.y + p.l.z * p.c.z);
	q44 += p.k;
	res.obj.mat[3][3] = q44;
	return (res);
}

t_vec4	get_surface_normal(t_surface s, t_vec4 hit_point)
{
	t_vec4	n;

	n = vec4_mat4_mul(hit_point, s.obj.mat);
	return (vec4_normalize(n));
}
