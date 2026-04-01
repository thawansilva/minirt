/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:49:34 by hermarti          #+#    #+#             */
/*   Updated: 2026/04/01 15:47:00 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "objects.h"
#include "rt_math.h"

t_surface_parameters	set_surface_parameters(t_vec3 c, t_vec3 w, t_vec3 l,
		float k)
{
	t_surface_parameters	parameters;

	ft_memset(&parameters, 0, sizeof(t_surface_parameters));
	vec3_copy(&parameters.c, c);
	vec3_copy(&parameters.w, w);
	vec3_copy(&parameters.l, l);
	parameters.k = k;
	return (parameters);
}

t_surface	create_surface(t_surface_parameters p)
{
	t_surface	res;
	float		q44;

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

t_vec3	get_surface_normal(t_surface s, t_vec3 hit_point)
{
	t_vec3	n;
	double	hp[4];

	hp[0] = hit_point.x;
	hp[1] = hit_point.y;
	hp[2] = hit_point.z;
	hp[3] = 1.0;
	n.x = s.obj.mat[0][0] * hp[0] + s.obj.mat[0][1] * hp[1] + s.obj.mat[0][2]
		* hp[2] + s.obj.mat[0][3] * hp[3];
	n.y = s.obj.mat[1][0] * hp[0] + s.obj.mat[1][1] * hp[1] + s.obj.mat[1][2]
		* hp[2] + s.obj.mat[1][3] * hp[3];
	n.z = s.obj.mat[2][0] * hp[0] + s.obj.mat[2][1] * hp[1] + s.obj.mat[2][2]
		* hp[2] + s.obj.mat[2][3] * hp[3];
	return (vec3_normalize(n));
}
