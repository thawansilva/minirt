/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 10:00:00 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/21 10:00:00 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_PARSER_H
# define TEST_PARSER_H

/* save_color tests */
void	test_save_color_basic(void **state);
void	test_save_color_black(void **state);
void	test_save_color_white(void **state);
void	test_save_color_red(void **state);
void	test_save_color_green(void **state);
void	test_save_color_blue(void **state);
void	test_save_color_mid_values(void **state);

/* save_vec4 tests */
void	test_save_vec4_basic(void **state);
void	test_save_vec4_integers(void **state);
void	test_save_vec4_zeros(void **state);
void	test_save_vec4_negative(void **state);
void	test_save_vec4_unit_vector(void **state);
void	test_save_vec4_normalized_diagonal(void **state);
void	test_save_vec4_large_values(void **state);

/* parse_ambient tests */
void	test_parse_ambient_basic(void **state);
void	test_parse_ambient_zero_lightness(void **state);
void	test_parse_ambient_full_lightness(void **state);
void	test_parse_ambient_mid_values(void **state);
void	test_parse_ambient_different_colors(void **state);

/* parse_camera tests */
void	test_parse_camera_basic(void **state);
void	test_parse_camera_different_position(void **state);
void	test_parse_camera_different_direction(void **state);
void	test_parse_camera_min_fov(void **state);
void	test_parse_camera_max_fov(void **state);
void	test_parse_camera_negative_coordinates(void **state);

/* parse_light tests */
void	test_parse_light_basic(void **state);
void	test_parse_light_different_position(void **state);
void	test_parse_light_zero_brightness(void **state);
void	test_parse_light_full_brightness(void **state);
void	test_parse_light_different_color(void **state);
void	test_parse_light_negative_coordinates(void **state);

/* parse_sphere tests */
void	test_parse_sphere_basic(void **state);
void	test_parse_sphere_different_position(void **state);
void	test_parse_sphere_different_diameter(void **state);
void	test_parse_sphere_red_color(void **state);
void	test_parse_sphere_not_bounded(void **state);
void	test_parse_sphere_large_diameter(void **state);
void	test_parse_sphere_small_diameter(void **state);

/* parse_plane tests */
void	test_parse_plane_basic(void **state);
void	test_parse_plane_different_position(void **state);
void	test_parse_plane_different_orientation(void **state);
void	test_parse_plane_diagonal_orientation(void **state);
void	test_parse_plane_red_color(void **state);
void	test_parse_plane_not_bounded(void **state);
void	test_parse_plane_negative_coordinates(void **state);

/* parse_cylinder tests */
void	test_parse_cylinder_basic(void **state);
void	test_parse_cylinder_different_position(void **state);
void	test_parse_cylinder_different_orientation(void **state);
void	test_parse_cylinder_large_dimensions(void **state);
void	test_parse_cylinder_small_dimensions(void **state);
void	test_parse_cylinder_diagonal_orientation(void **state);
void	test_parse_cylinder_is_bounded(void **state);
void	test_parse_cylinder_red_color(void **state);
void	test_parse_cylinder_negative_coordinates(void **state);

#endif
