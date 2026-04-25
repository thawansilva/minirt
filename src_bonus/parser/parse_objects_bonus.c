/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 18:48:34 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/22 18:51:10 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_memory_bonus.h"
#include "parser_bonus.h"

void	parse_sphere(char **arr, t_scene *scene)
{
	t_surface				*s;
	t_surface_parameters	s_params;

	s = &scene->surfaces[scene->idx_obj++];
	s_params = (t_surface_parameters){};
	save_vec4(arr[1], &s_params.coordinate);
	s_params.diameter = ft_atof(arr[2]);
	save_color(arr[3], &s_params.color);
	if	(ft_strcmp("co", arr[0]) == 0)
		s_params.type = CONE;
	else
		s_params.type = SPHERE;
	s_params.is_bounded = 0;
	*s = create_surface(s_params);
}

void	parse_plane(char **arr, t_scene *scene)
{
	t_surface				*s;
	t_surface_parameters	s_params;

	s = &scene->surfaces[scene->idx_obj++];
	s_params = (t_surface_parameters){};
	save_vec4(arr[1], &s_params.coordinate);
	save_vec4(arr[2], &s_params.orientation);
	save_color(arr[3], &s_params.color);
	if	(ft_strcmp("hy", arr[0]) == 0)
		s_params.type = HYPERBOLOID;
	else if (ft_strcmp("pa", arr[0]) == 0)
		s_params.type = PARABOLOID;
	else
		s_params.type = PLANE;
	s_params.is_bounded = 0;
	*s = create_surface(s_params);
}

void	parse_cylinder(char **arr, t_scene *scene)
{
	t_surface				*s;
	t_surface_parameters	s_params;

	s = &scene->surfaces[scene->idx_obj++];
	s_params = (t_surface_parameters){};
	save_vec4(arr[1], &s_params.coordinate);
	save_vec4(arr[2], &s_params.orientation);
	s_params.diameter = ft_atof(arr[3]);
	s_params.height = ft_atof(arr[4]);
	save_color(arr[5], &s_params.color);
	s_params.type = CYLINDER;
	s_params.is_bounded = 1;
	*s = create_surface(s_params);
	s->is_bounded = 1;
}
