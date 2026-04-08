/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:16:25 by hermarti          #+#    #+#             */
/*   Updated: 2026/04/08 16:19:12 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATH_H
# define RT_MATH_H

# include "objects.h"

void	vec4_copy(t_vec4 *a, t_vec4 b);
double	vec4_mag(t_vec4 v);
t_vec4	vec4_normalize(t_vec4 v);
t_vec4	vec4_mat4_mul(t_vec4 v, double m[4][4]);
double	vec4_dot_prod(t_vec4 a, t_vec4 b);
t_vec4	vec4_cross_prod(t_vec4 a, t_vec4 b);
t_vec4	vec4_scale(t_vec4 v, double scalar);
t_vec4	vec4_add(t_vec4 a, t_vec4 b);
t_vec4	vec4_sub(t_vec4 a, t_vec4 b);
t_vec4	vec4_reflect(t_vec4 v, t_vec4 n);

typedef struct s_intersection_vars
{
	double	a;
	double	b;
	double	c;
	double	delta;
}				t_intersection_vars;

double	intersection(t_ray *ray, t_surface *surf);

#endif
