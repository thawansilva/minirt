/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:56:20 by hermarti          #+#    #+#             */
/*   Updated: 2026/04/16 13:56:45 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_math_bonus.h"

static t_mat4	fill_rotation_mat(t_vec4 ax, double c, double s,
		double tc)
{
	t_mat4	res;

	ft_memset(&res, 0, sizeof(t_mat4));
	res.m[0][0] = c + ax.x * ax.x * tc;
	res.m[0][1] = ax.x * ax.y * tc - ax.z * s;
	res.m[0][2] = ax.x * ax.z * tc + ax.y * s;
	res.m[1][0] = ax.y * ax.x * tc + ax.z * s;
	res.m[1][1] = c + ax.y * ax.y * tc;
	res.m[1][2] = ax.y * ax.z * tc - ax.x * s;
	res.m[2][0] = ax.z * ax.x * tc - ax.y * s;
	res.m[2][1] = ax.z * ax.y * tc + ax.x * s;
	res.m[2][2] = c + ax.z * ax.z * tc;
	res.m[3][3] = 1.0;
	return (res);
}

t_mat4	mat4_rotation_from_to(t_vec4 from, t_vec4 to)
{
	t_mat4	res;
	t_vec4	axis;
	double	cos_a;
	double	sin_a;

	ft_memset(&res, 0, sizeof(t_mat4));
	cos_a = vec4_dot_prod(vec4_normalize(from), vec4_normalize(to));
	axis = vec4_cross_prod(vec4_normalize(from), vec4_normalize(to));
	sin_a = vec4_mag(axis);
	if (sin_a < 1e-6)
	{
		res.m[0][0] = 1.0;
		if (cos_a > 0)
			res.m[1][1] = 1.0;
		else
			res.m[1][1] = -1.0;
		res.m[2][2] = 1.0;
		res.m[3][3] = 1.0;
		return (res);
	}
	res = fill_rotation_mat(vec4_normalize(axis), cos_a, sin_a, 1.0 - cos_a);
	return (res);
}
