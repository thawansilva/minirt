/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 13:43:13 by hermarti          #+#    #+#             */
/*   Updated: 2026/03/31 13:53:46 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "rt_math.h"
#include <math.h>

static float	calculate_a_val(t_ray *ray, t_surface *surf)
{
	t_vec4	tmp_a;

	tmp_a = vec4_mat4_mul(ray->dir, surf->obj.mat);
	return (vec4_dot_prod(tmp_a, ray->dir));
}

static float	calculate_b_val(t_ray *ray, t_surface *surf)
{
	t_vec4	tmp_b;

	tmp_b = vec4_mat4_mul(ray->dir, surf->obj.mat);
	return (2.0f * vec4_dot_prod(tmp_b, ray->orig));
}

static float	calculate_c_val(t_ray *ray, t_surface *surf)
{
	t_vec4	tmp_c;

	tmp_c = vec4_mat4_mul(ray->orig, surf->obj.mat);
	return (vec4_dot_prod(tmp_c, ray->orig));
}

float	intersection(t_ray *ray, t_surface *surf)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	x1;
	float	x2;

	a = calculate_a_val(ray, surf);
	b = calculate_b_val(ray, surf);
	c = calculate_c_val(ray, surf);
	if (a == 0.0f)
	{
		if (b == 0.0f)
			return (NAN);
		x1 = -c / b;
		if (x1 > 0.0f)
			return (x1);
		return (NAN);
	}
	delta = powf(b, 2.0f) - (4.0f * a * c);
	if (delta < 0)
		return (NAN);
	x1 = (-b + sqrtf(delta)) / (2.0f * a);
	x2 = (-b - sqrtf(delta)) / (2.0f * a);
	if (x2 > 0)
		return (x2);
	if (x1 > 0)
		return (x1);
	return (NAN);
}
