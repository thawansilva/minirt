/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 09:36:51 by hermarti          #+#    #+#             */
/*   Updated: 2026/04/27 14:54:59 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "minirt.h"

void	*init_window(t_window *window, int width, int height, char *window_name)
{
	ft_memset(window, 0, sizeof(t_window));
	window->width = width;
	window->height = height;
	window->mlx = mlx_init();
	window->x_window = mlx_new_window(window->mlx, window->width,
			window->height, window_name);
	if (!init_img_buffer(window))
	{
		destroy_window(window);
		return (NULL);
	}
	return (window);
}

void	*destroy_window(t_window *window)
{
	destroy_img_buffer(window);
	mlx_destroy_window(window->mlx, window->x_window);
	mlx_destroy_display(window->mlx);
	free(window->mlx);
	window = NULL;
	return (NULL);
}

void	set_window_hooks(t_env *env)
{
	mlx_mouse_hook(env->window.x_window, mouse_hook, env);
	mlx_key_hook(env->window.x_window, key_hook, env);
	mlx_hook(env->window.x_window, 17, 1L << 0, close_window, env);
}

int	close_window(t_env *env)
{
	mlx_loop_end(env->window.mlx);
	return (0);
}
