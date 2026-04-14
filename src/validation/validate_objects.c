/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:48:47 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/13 22:07:06 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

int	is_valid_ambient(char **arr)
{
	if (!arr || !arr[1] || !arr[2])
		return (0);
	if (!is_valid_ratio(arr[1]) || !is_valid_color(arr[2]))
		return (0);
	return (1);
}

int	is_valid_camera(char **arr)
{
	if (!arr || !arr[1] || !arr[2] || !arr[3])
		return (0);
	if (!is_valid_coordinates(arr[1]) || !is_valid_normalized_vector(arr[2])
		|| !is_valid_fov(arr[3]))
		return (0);
	return (1);
}

int	is_valid_light(char **arr)
{
	if (!arr || !arr[1] || !arr[2] || !arr[3])
		return (0);
	if (!is_valid_coordinates(arr[1]) || !is_valid_ratio(arr[2])
		|| !is_valid_color(arr[3]))
		return (0);
	return (1);
}

int	is_valid_sphere(char **arr)
{
	if (!arr || !arr[1] || !arr[2] || !arr[3])
		return (0);
	if (!is_valid_coordinates(arr[1]))
		return (0);
	if (!is_valid_float(arr[2]) || ft_atof(arr[2]) < 0.0)
		return (0);
	if (!is_valid_color(arr[3]))
		return (0);
	return (1);
}

int	is_valid_plane(char **arr)
{
	if (!arr || !arr[1] || !arr[2] || !arr[3])
		return (0);
	if (!is_valid_coordinates(arr[1]) || !is_valid_normalized_vector(arr[2])
		|| !is_valid_color(arr[3]))
		return (0);
	return (1);
}

int	is_valid_cylinder(char **arr)
{
	if (!arr || !arr[1] || !arr[2] || !arr[3] || !arr[4] || !arr[5])
		return (0);
	if (!is_valid_coordinates(arr[1]) || !is_valid_normalized_vector(arr[2]))
		return (0);
	if (!is_valid_float(arr[3]) || ft_atof(arr[3]) <= 0.0)
		return (0);
	if (!is_valid_float(arr[4]) || ft_atof(arr[4]) <= 0.0)
		return (0);
	if (!is_valid_color(arr[5]))
		return (0);
	return (1);
}
