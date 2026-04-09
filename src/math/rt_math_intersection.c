/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 13:43:13 by hermarti          #+#    #+#             */
/*   Updated: 2026/04/08 16:17:59 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "objects.h"
#include "rt_math.h"
#include <math.h>

static double	calculate_a_val(t_ray *ray, t_surface *surf)
{
	t_vec4	tmp_a;

	tmp_a = vec4_mat4_mul(ray->dir, surf->obj.mat);
	return (vec4_dot_prod(tmp_a, ray->dir));
}

static double	calculate_b_val(t_ray *ray, t_surface *surf)
{
	t_vec4	tmp_b;

	tmp_b = vec4_mat4_mul(ray->dir, surf->obj.mat);
	return (2.0f * vec4_dot_prod(tmp_b, ray->orig));
}

static double	calculate_c_val(t_ray *ray, t_surface *surf)
{
	t_vec4	tmp_c;

	tmp_c = vec4_mat4_mul(ray->orig, surf->obj.mat);
	return (vec4_dot_prod(tmp_c, ray->orig));
}

double	intersection(t_ray *ray, t_surface *surf)
{
	t_intersection_vars	vars;
	double				x1;
	double				x2;

	ft_memset(&vars, 0, sizeof(t_intersection_vars));
	vars.a = calculate_a_val(ray, surf);
	vars.b = calculate_b_val(ray, surf);
	vars.c = calculate_c_val(ray, surf);
	if (vars.a == 0.0 && vars.b == 0.0)
		return (NAN);
	if (vars.a == 0.0 && (-vars.c / vars.b) > 0.0)
		return (-vars.c / vars.b);
	if (vars.a == 0.0)
		return (NAN);
	vars.delta = (vars.b * vars.b) - (4.0 * vars.a * vars.c);
	if (vars.delta < 0.0)
		return (NAN);
	x1 = (-vars.b + sqrt(vars.delta)) / (2.0 * vars.a);
	x2 = (-vars.b - sqrt(vars.delta)) / (2.0 * vars.a);
	if (x2 > 0.0)
		return (x2);
	if (x1 > 0.0)
		return (x1);
	return (NAN);
}
