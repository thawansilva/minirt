/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 13:43:23 by hermarti          #+#    #+#             */
/*   Updated: 2026/04/01 15:50:42 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "rt_math.h"
#include <math.h>

void	vec3_copy(t_vec3 *a, t_vec3 b)
{
	a->x = b.x;
	a->y = b.y;
	a->z = b.z;
}

float	vec3_mag(t_vec3 v)
{
	return (sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

t_vec3	vec3_normalize(t_vec3 v)
{
	t_vec3	res;
	float	mag;

	mag = vec3_mag(v);
	res.x = v.x / mag;
	res.y = v.y / mag;
	res.z = v.z / mag;
	return (res);
}

t_vec4	vec4_mat4_mul(t_vec4 v, float m[4][4])
{
	t_vec4	res;

	res.x = (m[0][0] * v.x) + (m[0][1] * v.y) + (m[0][2] * v.z) + (m[0][3]
			* v.k);
	res.y = (m[1][0] * v.x) + (m[1][1] * v.y) + (m[1][2] * v.z) + (m[1][3]
			* v.k);
	res.z = (m[2][0] * v.x) + (m[2][1] * v.y) + (m[2][2] * v.z) + (m[2][3]
			* v.k);
	res.k = (m[3][0] * v.x) + (m[3][1] * v.y) + (m[3][2] * v.z) + (m[3][3]
			* v.k);
	return (res);
}

float	vec4_dot_prod(t_vec4 a, t_vec4 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.k * b.k));
}
