/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 13:43:13 by hermarti          #+#    #+#             */
/*   Updated: 2026/04/15 17:05:34 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "rt_math.h"
#include <math.h>

static double	check_hit(double x, t_ray *ray, t_surface *surf)
{
	t_vec4	hit_p;
	t_vec4	cp;
	double	h;

	if (x <= 0.0001)
		return (NAN);
	hit_p = vec4_add(ray->orig, vec4_scale(ray->dir, x));
	cp = vec4_sub(hit_p, surf->obj.coordinate);
	h = vec4_dot_prod(cp, surf->obj.orientation);
	if (surf->is_bounded && (h >= surf->obj.min && h <= surf->obj.max))
		return (x);
	else if (!surf->is_bounded)
		return (x);
	return (NAN);
}

static double	solve_quadratic(t_intersection_vars *v, double *x)
{
	double	tmp;

	v->delta = (v->b * v->b) - (4.0 * v->a * v->c);
	if (v->delta < 0.0)
		return (0);
	x[0] = (-v->b + sqrt(v->delta)) / (2.0 * v->a);
	x[1] = (-v->b - sqrt(v->delta)) / (2.0 * v->a);
	if (x[0] > x[1])
	{
		tmp = x[0];
		x[0] = x[1];
		x[1] = tmp;
	}
	return (1);
}

double	intersection(t_ray *ray, t_surface *surf)
{
	t_intersection_vars	v;
	double				x[2];
	double				tmp;

	v.a = vec4_dot_prod(vec4_mat4_mul(ray->dir, surf->obj.mat), ray->dir);
	v.b = vec4_dot_prod(vec4_mat4_mul(ray->dir, surf->obj.mat), ray->orig)
		* 2.0;
	v.c = vec4_dot_prod(vec4_mat4_mul(ray->orig, surf->obj.mat), ray->orig);
	if (v.a == 0.0)
	{
		if (v.b != 0.0 && (-v.c / v.b) > 0.0)
			return (-v.c / v.b);
		return (NAN);
	}
	if (!solve_quadratic(&v, x))
		return (NAN);
	tmp = check_hit(x[0], ray, surf);
	if (!isnan(tmp))
		return (tmp);
	return (check_hit(x[1], ray, surf));
}
