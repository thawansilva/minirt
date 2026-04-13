/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_properties.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 13:29:00 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/11 15:10:18 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"
#include "libft.h"

int	is_valid_ratio(char *str)
{
	float	value;

	if (str == NULL || str[0] == '\0')
		return (0);
	value = ft_atof(str);
	if (!is_valid_float(str) || value < 0.0 || value > 1.0)
		return (0);
	return (1);
}

int	is_valid_color(char *str)
{
	int		i;
	int		value;
	char	**colors;

	if (str == NULL || str[0] == '\0')
		return (0);
	colors = ft_split(str, ',');
	if (colors == NULL)
		return (0);
	i = -1;
	while (colors[++i])
	{
		value = ft_atoi(colors[i]);
		if (!is_valid_int(colors[i]) || value < 0 || value > 255)
		{
			free_arr(colors);
			return (0);
		}
	}
	free_arr(colors);
	if (i != 3)
		return (0);
	return (1);
}

int	is_valid_coordinates(char *str)
{
	int		i;
	char	**coordinates;

	if (str == NULL)
		return (0);
	coordinates = ft_split(str, ',');
	if (coordinates == NULL)
		return (0);
	i = 0;
	while (coordinates[i])
	{
		if (!is_valid_float(coordinates[i]))
		{
			free_arr(coordinates);
			return (0);
		}
		i++;
	}
	free_arr(coordinates);
	if (i != 3)
		return (0);
	return (1);
}

int	is_valid_normalized_vector(char *str)
{
	int		i;
	float	value;
	char	**vectors;

	if (str == NULL || str[0] == '\0')
		return (0);
	i = -1;
	vectors = ft_split(str, ',');
	if (vectors == NULL)
		return (0);
	while (vectors[++i])
	{
		value = ft_atof(vectors[i]);
		if (!is_valid_float(vectors[i]) || value < -1.0 || value > 1.0)
		{
			free_arr(vectors);
			return (0);
		}
	}
	free_arr(vectors);
	if (i != 3)
		return (0);
	return (1);
}

int	is_valid_fov(char *str)
{
	int	i;
	int	fov;

	if (str == NULL || str[0] == '\0')
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	fov = ft_atoi(str);
	if (fov < 0 || fov > 180)
		return (0);
	return (1);
}
