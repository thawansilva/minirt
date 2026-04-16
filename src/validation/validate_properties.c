/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_properties.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 13:29:00 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/15 20:47:23 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"
#include "libft.h"

int	is_valid_extension(char *file)
{
	int		len;
	char	*extension;

	if (!file)
	{
		show_error("Invalid file");
		return (0);
	}
	len = ft_strlen(file);
	extension = ft_strrchr(file, '.');
	if (!extension || len <= 3 || ft_strcmp(".rt", extension) != 0)
	{
		show_error("Invalid extension");
		return (0);
	}
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
	int	fov;

	if (str == NULL || str[0] == '\0' || !is_valid_int(str))
		return (0);
	fov = ft_atoi(str);
	if (fov < 0 || fov > 180)
		return (0);
	return (1);
}
