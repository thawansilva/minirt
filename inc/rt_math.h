/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:16:25 by hermarti          #+#    #+#             */
/*   Updated: 2026/04/15 17:16:57 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATH_H
# define RT_MATH_H

# include "objects.h"

void	vec4_copy(t_vec4 *a, t_vec4 b);
double	vec4_mag(t_vec4 v);
t_vec4	vec4_normalize(t_vec4 v);
t_vec4	vec4_mat4_mul(t_vec4 v, t_mat4 m);
double	vec4_dot_prod(t_vec4 a, t_vec4 b);
t_vec4	vec4_cross_prod(t_vec4 a, t_vec4 b);
t_vec4	vec4_scale(t_vec4 v, double scalar);
t_vec4	vec4_add(t_vec4 a, t_vec4 b);
t_vec4	vec4_sub(t_vec4 a, t_vec4 b);
t_vec4	vec4_reflect(t_vec4 v, t_vec4 n);

t_mat4	mat4_rotation_from_to(t_vec4 from, t_vec4 to);
t_mat4	mat4_transpose(t_mat4 m);
t_mat4	mat4_mat4_mult(t_mat4 m1, t_mat4 m2);

typedef struct s_intersection_vars
{
	double	a;
	double	b;
	double	c;
	double	delta;
}				t_intersection_vars;

double	intersection(t_ray *ray, t_surface *surf);

#endif
