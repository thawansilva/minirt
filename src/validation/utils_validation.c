/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 22:07:36 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/13 22:09:42 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

void	show_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}
