/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_number_values.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 22:07:36 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/15 20:55:56 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "validation_bonus.h"
#include "free_memory_bonus.h"

int	is_valid_float(const char *str)
{
	int	has_digits;

	has_digits = 0;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
	{
		has_digits = 1;
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			has_digits = 1;
			str++;
		}
	}
	return (has_digits && *str == '\0');
}

int	is_valid_int(const char *str)
{
	if (str == NULL || *str == '\0')
		return (0);
	while (ft_isdigit(*str))
		str++;
	if (*str == '\n')
		str++;
	return (*str == '\0');
}

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
