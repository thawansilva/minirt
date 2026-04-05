/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_properties.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 13:29:00 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/05 16:35:26 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>
#include <math.h>

float ft_strtof(const char *str, char **endptr) {
    const char *p = str;
    int sign = 1;
    float result = 0.0f;
    float fraction = 0.0f;
    float divisor = 10.0f;
    int exponent = 0;
    int exp_sign = 1;

    // Ignorar espaços em branco
    while (isspace((unsigned char)*p)) p++;

    // Sinal
    if (*p == '+') {
        p++;
    } else if (*p == '-') {
        sign = -1;
        p++;
    }

    // Parte inteira
    while (isdigit((unsigned char)*p)) {
        result = result * 10.0f + (*p - '0');
        p++;
    }

    // Parte fracionária
    if (*p == '.') {
        p++;
        while (isdigit((unsigned char)*p)) {
            fraction += (*p - '0') / divisor;
            divisor *= 10.0f;
            p++;
        }
        result += fraction;
    }

    // Parte exponencial
    if (*p == 'e' || *p == 'E') {
        p++;
        if (*p == '+') {
            p++;
        } else if (*p == '-') {
            exp_sign = -1;
            p++;
        }
        while (isdigit((unsigned char)*p)) {
            exponent = exponent * 10 + (*p - '0');
            p++;
        }
        result *= powf(10.0f, exp_sign * exponent);
    }

    if (endptr) {
        *endptr = (char *)p;
    }
    return sign * result;
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

int	is_valid_ratio(char *str)
{
	float	value;

	if (str == NULL)
		return (0);
	value = ft_atof(str);
	if (value < 0.0 || value > 1.0)
		return (0);
	return (1);
}

int	is_valid_color(char *str)
{
	int		i;
	int		value;
	char	**colors;

	if (str == NULL)
		return (0);
	colors = ft_split(str, ',');
	if (colors == NULL)
		return (0);
	i = 0;
	while (colors[i])
	{
		value = ft_atoi(str);
		if (value < 0 || value > 255)
		{
			free_arr(colors);
			return (0);
		}
		i++;
	}
	free_arr(colors);
	if (--i != 3)
		return (0);
	return (1);
}

int	is_valid_coordinates(char *str)
{
	int		i;
	float	value;
	char	**coordinates;

	if (str == NULL)
		return (0);
	coordinates = ft_split(str, ',');
	if (coordinates == NULL)
		return (0);
	i = 0;
	while (colors[i])
	{
		value = ft_atoi(str);
		if (value < 0 || value > 255)
		{
			free_arr(colors);
			return (0);
		}
		i++;
	}
	free_arr(coordinates);
	if (--i != 3)
		return (0);
	return (1);
}

int	is_valid_normalized_vector(char *str)
{
	colors = ft_split(str, ',');
	if (colors == NULL)
		return (0);
	i = 0;
	while (colors[i])
	{
		value = ft_atoi(str);
		if (value < 0 || value > 255)
		{
			free_arr(colors);
			return (0);
		}
		i++;
	}
	free_arr(colors);
	if (--i != 3)
		return (0);
	return (1);
}
