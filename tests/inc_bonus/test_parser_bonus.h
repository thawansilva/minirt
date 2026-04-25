/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 10:00:00 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/25 10:00:00 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_PARSER_BONUS_H
# define TEST_PARSER_BONUS_H

/* parse_cone tests */
void	test_parse_cone_basic(void **state);
void	test_parse_cone_offset_position(void **state);
void	test_parse_cone_diameter_variations(void **state);
void	test_parse_cone_red_color(void **state);
void	test_parse_cone_black_color(void **state);
void	test_parse_cone_negative_coordinates(void **state);
void	test_parse_cone_decimal_coordinates(void **state);
void	test_parse_cone_unbounded(void **state);
void	test_parse_cone_multiple_cones(void **state);

/* parse_hyperboloid tests */
void	test_parse_hyperboloid_basic(void **state);
void	test_parse_hyperboloid_offset_position(void **state);
void	test_parse_hyperboloid_different_orientations(void **state);
void	test_parse_hyperboloid_red_color(void **state);
void	test_parse_hyperboloid_negative_coordinates(void **state);
void	test_parse_hyperboloid_diagonal_orientation(void **state);
void	test_parse_hyperboloid_unbounded(void **state);
void	test_parse_hyperboloid_multiple_hyperboloids(void **state);

/* parse_paraboloid tests */
void	test_parse_paraboloid_basic(void **state);
void	test_parse_paraboloid_offset_position(void **state);
void	test_parse_paraboloid_different_orientations(void **state);
void	test_parse_paraboloid_green_color(void **state);
void	test_parse_paraboloid_negative_coordinates(void **state);
void	test_parse_paraboloid_z_axis_orientation(void **state);
void	test_parse_paraboloid_unbounded(void **state);
void	test_parse_paraboloid_multiple_paraboloids(void **state);
void	test_parse_paraboloid_blue_color(void **state);

/* mixed bonus objects tests */
void	test_parse_mixed_bonus_objects(void **state);
void	test_parse_bonus_objects_color_variation(void **state);

#endif
