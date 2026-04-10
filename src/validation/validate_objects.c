/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:48:47 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/09 21:00:05 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

int	is_valid_ambient(char **arr)
{
	if (!is_valid_ratio(arr[0]) || !is_valid_color(arr[1]))
		return (0);
	return (1);
}

int	is_valid_camera(char **arr)
{
	(void) arr;
	if (!is_valid_coordinates(arr[0]))
		return (0);
	// Validate normalized vector
	if (!is_valid_normalized_vector(arr[1]))
		return (0);
	// Validate FOV
	if (!is_valid_fov(arr[2]))
		return (0);
	return (1);
}

int	is_valid_light(char **arr)
{
	(void) arr;
	// Validate coordinate
	if (!is_valid_coordinates(arr[0]))
		return (0);
	// Validate bright ratio
	if (!is_valid_ratio(arr[1]))
		return (0);
	// Validate color
	if (!is_valid_color(arr[2]))
		return (0);
	return (1);
}

int	is_valid_sphere(char **arr)
{
	(void) arr;
	// Validate coordinate
	if (!is_valid_coordinates(arr[0]))
		return (0);
	// Validate diameter
	// Validate color
	if (!is_valid_color(arr[2]))
		return (0);
	return (1);
}

int	is_valid_plane(char **arr)
{
	(void) arr;
	// Validate coordinate
	if (!is_valid_coordinates(arr[0]))
		return (0);
	// Validate normalized vector
	if (!is_valid_normalized_vector(arr[1]))
		return (0);
	// Validate color
	if (!is_valid_color(arr[2]))
		return (0);
	return (1);
}

int	is_valid_cylinder(char **arr)
{
	(void) arr;
	// Validate coordinate
	if (!is_valid_coordinates(arr[1]))
		return (0);
	// Validate normalized vector
	if (!is_valid_normalized_vector(arr[2]))
		return (0);
	// Validate diameter
	if (!is_valid_float(arr[3]))
		return (0);
	// Validate height
	if (!is_valid_float(arr[4]))
		return (0);
	// Validate color
	if (!is_valid_color(arr[2]))
		return (0);
	return (1);
}
