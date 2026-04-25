/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 18:48:52 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/22 18:48:54 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "objects_bonus.h"
#include "free_memory_bonus.h"

void	save_color(const char *token, t_color *dst)
{
	char	**rgb;

	rgb = ft_split(token, ',');
	dst->r = (unsigned char)ft_atoi(rgb[0]);
	dst->g = (unsigned char)ft_atoi(rgb[1]);
	dst->b = (unsigned char)ft_atoi(rgb[2]);
	free_arr(rgb);
}

void	save_vec4(const char *token, t_vec4 *dst)
{
	char	**coordinates;

	coordinates = ft_split(token, ',');
	dst->x = ft_atof(coordinates[0]);
	dst->y = ft_atof(coordinates[1]);
	dst->z = ft_atof(coordinates[2]);
	dst->k = 0.0;
	free_arr(coordinates);
}
