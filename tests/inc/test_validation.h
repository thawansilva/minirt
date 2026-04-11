/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_validation.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 08:54:36 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/11 15:25:58 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_VALIDATION_H
# define TEST_VALIDATION_H

void test_valid_extension(void **state);
void test_invalid_extension(void **state);
void test_split_spaces(void **state);
// Validate File
void test_read_file_valid(void **state);
void test_read_file_invalid(void **state);
void test_read_file_empty(void **state);
// Validate Ratio
void test_valid_ratio_zero(void **state);
void test_valid_ratio_one(void **state);
void test_valid_ratio_mid(void **state);
void test_valid_ratio_negative(void **state);
void test_valid_ratio_above_one(void **state);
void test_valid_ratio_null(void **state);
void test_valid_ratio_non_numeric(void **state);
void test_valid_ratio_empty_string(void **state);
// Validate Color
void test_valid_color_valid(void **state);
void test_valid_color_null(void **state);
void test_valid_color_too_few_components(void **state);
void test_valid_color_too_many_components(void **state);
void test_valid_color_out_of_range_high(void **state);
void test_valid_color_out_of_range_low(void **state);
void test_valid_color_boundary_zero(void **state);
void test_valid_color_boundary_max(void **state);
void test_valid_color_non_numeric(void **state);
void test_valid_color_empty_string(void **state);
// Validate Coordinates
void test_valid_coordinates_valid(void **state);
void test_valid_coordinates_valid_int_values(void **state);
void test_valid_coordinates_null(void **state);
void test_valid_coordinates_too_few(void **state);
void test_valid_coordinates_too_many(void **state);
void test_valid_coordinates_negative(void **state);
void test_valid_coordinates_without_decimal(void **state);
void test_valid_coordinates_decimal(void **state);
void test_valid_coordinates_numeric_with_non_numeric(void **state);
void test_valid_coordinates_non_numeric(void **state);
void test_valid_coordinates_empty_string(void **state);
// Validate normal vector
void test_valid_normal(void **state);
void test_invalid_normal(void **state);
// Validate fov
void test_valid_fov(void **state);
void test_invalid_fov(void **state);
void test_valid_ambient(void **state);
void test_duplicate_ambient(void **state);
void test_valid_camera(void **state);
void test_valid_light(void **state);
void test_valid_sphere(void **state);
void test_valid_plane(void **state);
void test_valid_cylinder(void **state);
void test_invalid_identifier(void **state);
void test_wrong_arg_count(void **state);
void test_valid_scene(void **state);
void test_missing_camera(void **state);
#endif
