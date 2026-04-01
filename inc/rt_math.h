/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:16:25 by hermarti          #+#    #+#             */
/*   Updated: 2026/04/01 15:51:16 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATH_H
# define RT_MATH_H

# include "objects.h"

void	vec3_copy(t_vec3 *a, t_vec3 b);
float	vec3_mag(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);
t_vec4	vec4_mat4_mul(t_vec4 v, float m[4][4]);
float	vec4_dot_prod(t_vec4 a, t_vec4 b);
float	intersection(t_ray *ray, t_surface *surf);

#endif
