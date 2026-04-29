/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_scene_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <thaperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:48:47 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/28 18:09:17 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation_bonus.h"

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

int	has_enough_elements(t_obj_count obj_count)
{
	char	has_error;

	has_error = 0;
	if (obj_count.ambient != 1 && has_error++)
		show_error("It should have one ambient");
	else if (obj_count.camera != 1 && has_error++)
		show_error("It should have one camera");
	else if (obj_count.light == 0 && has_error++)
		show_error("It should have one light");
	else if (obj_count.obj == 0 && has_error++)
		show_error("No objects in the scene");
	return (has_error == 0);
}
