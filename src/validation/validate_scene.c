/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:48:47 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/15 20:43:16 by thaperei         ###   ########.fr       */
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
