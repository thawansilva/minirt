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
#include <ctype.h>
#include <math.h>

//float	ft_strtof(const char *str, char **endptr) {
//    const char *p = str;
//    int sign = 1;
//    float result = 0.0f;
//    float fraction = 0.0f;
//    float divisor = 10.0f;
//    int exponent = 0;
//    int exp_sign = 1;
//
//    // Ignorar espaços em branco
//    while (ft_isspace((unsigned char)*p)) p++;
//
//    // Sinal
//    if (*p == '+') {
//        p++;
//    } else if (*p == '-') {
//        sign = -1;
//        p++;
//    }
//
//    // Parte inteira
//    while (ft_isdigit((unsigned char)*p)) {
//        result = result * 10.0f + (*p - '0');
//        p++;
//    }
//
//    // Parte fracionária
//    if (*p == '.') {
//        p++;
//        while (ft_isdigit((unsigned char)*p)) {
//            fraction += (*p - '0') / divisor;
//            divisor *= 10.0f;
//            p++;
//        }
//        result += fraction;
//    }
//
//    // Parte exponencial
//    if (*p == 'e' || *p == 'E') {
//        p++;
//        if (*p == '+') {
//            p++;
//        } else if (*p == '-') {
//            exp_sign = -1;
//            p++;
//        }
//        while (ft_isdigit((unsigned char)*p)) {
//            exponent = exponent * 10 + (*p - '0');
//            p++;
//        }
//        result *= powf(10.0f, exp_sign * exponent);
//    }
//
//    if (endptr) {
//        *endptr = (char *)p;
//    }
//    return sign * result;
//}

//int	is_valid_float(const char *str)
//{
//	int has_digits_before;
//	int has_digits_after;
//	int has_dot;
//
//	has_digits_before = 0;
//	has_digits_after = 0;
//	has_dot = 0;
//	if (*str == '+' || *str == '-')
//		str++;
//	while (ft_isdigit(*str))
//	{
//		has_digits_before = 1;
//		str++;
//	}
//	if (*str++ == '.')
//		has_dot = 1;
//	else
//		return 0;
//	while (ft_isdigit(*str))
//	{
//		has_digits_after = 1;
//		str++;
//	}
//	if (has_digits_before && has_dot && has_digits_after)
//		return 1;
//	return 0;
//}

int is_valid_float(const char *str)
{
	int has_digits;

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

int	is_valid_int(char *str)
{
	if (str == NULL || *str == '\0')
		return (0);
	while (ft_isdigit(*str))
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

	i = 0;
	if (str == NULL || str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ',')
			return (0);
		i++;
	}
	i = 0;
	colors = ft_split(str, ',');
	if (colors == NULL)
		return (0);
	while (colors[i])
	{
		value = ft_atoi(colors[i]);
		if (value < 0 || value > 255)
		{
			free_arr(colors);
			return (0);
		}
		i++;
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
	int		value;
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
