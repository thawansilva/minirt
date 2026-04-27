/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 09:16:45 by hermarti          #+#    #+#             */
/*   Updated: 2026/04/27 09:45:47 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"
#include "parser.h"
#include "minirt.h"
#include "libft.h"
#include "minirt.h"
#include "free_memory.h"
#include <stdlib.h>

void	*init_env(t_env *env, int argc, char **argv)
{
	ft_memset(env, 0, sizeof(t_env));
	if (argc != 2)
	{
		show_error("Usage: ./miniRT <file>");
		return (NULL);
	}
	if (is_valid_input(argv[1], &env->scene))
		parse_elements(&env->scene);
	return (env);
}

void	*destroy_env(t_env *env)
{
	destroy_window(&env->window);
	free_scene(&env->scene);
	env = NULL;
	return (NULL);
}
