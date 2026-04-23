/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 16:00:03 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/22 19:34:13 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"
#include "free_memory.h"
#include "parser.h"
#include "libft.h"

int	main(int argc, char *argv[])
{
	t_scene	scene;

	scene = (t_scene){};
	if (argc != 2)
	{
		show_error("Usage: ./miniRT <file>");
		return (0);
	}
	if (is_valid_input(argv[1], &scene))
		parse_elements(&scene);
	free_scene(&scene);
	return (0);
}
