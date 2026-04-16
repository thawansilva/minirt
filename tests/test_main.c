/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 08:54:40 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/15 19:43:24 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "libft.h"
#include "test_validation.h"
#include <stdio.h>
#include <string.h>

static int	run_validation_tests(void)
{
	const struct CMUnitTest tests[] = {
		// Validation setup tests
		cmocka_unit_test(test_valid_extension),
		cmocka_unit_test(test_invalid_extension),
		cmocka_unit_test(test_split_spaces),
		cmocka_unit_test(test_read_file_valid),
		cmocka_unit_test(test_read_file_invalid),
		cmocka_unit_test(test_read_file_empty),
		cmocka_unit_test(test_valid_float_integer),
		cmocka_unit_test(test_valid_float_positive),
		cmocka_unit_test(test_valid_float_negative),
		cmocka_unit_test(test_valid_float_explicit_plus),
		cmocka_unit_test(test_valid_float_leading_dot),
		cmocka_unit_test(test_valid_float_trailing_dot),
		cmocka_unit_test(test_valid_float_only_dot),
		cmocka_unit_test(test_valid_float_only_sign),
		cmocka_unit_test(test_valid_float_empty),
		cmocka_unit_test(test_valid_float_non_numeric),
		cmocka_unit_test(test_valid_float_spaces),
		cmocka_unit_test(test_valid_float_multiple_dots),
		cmocka_unit_test(test_valid_int_positive),
		cmocka_unit_test(test_valid_int_zero),
		cmocka_unit_test(test_valid_int_null),
		cmocka_unit_test(test_valid_int_empty),
		cmocka_unit_test(test_valid_int_negative),
		cmocka_unit_test(test_valid_int_explicit_plus),
		cmocka_unit_test(test_valid_int_with_newline),
		cmocka_unit_test(test_valid_int_non_numeric),
		cmocka_unit_test(test_valid_int_float),
		cmocka_unit_test(test_valid_int_leading_zeros),
		cmocka_unit_test(test_valid_int_max_int),
		cmocka_unit_test(test_valid_int_alphanumeric),
		cmocka_unit_test(test_valid_int_only_newline_after_digits),
		cmocka_unit_test(test_valid_ratio_zero),
		cmocka_unit_test(test_valid_ratio_one),
		cmocka_unit_test(test_valid_ratio_mid),
		cmocka_unit_test(test_valid_ratio_negative),
		cmocka_unit_test(test_valid_ratio_above_one),
		cmocka_unit_test(test_valid_ratio_null),
		cmocka_unit_test(test_valid_ratio_non_numeric),
		cmocka_unit_test(test_valid_ratio_empty_string),
		cmocka_unit_test(test_valid_color_valid),
		cmocka_unit_test(test_valid_color_null),
		cmocka_unit_test(test_valid_color_too_few_components),
		cmocka_unit_test(test_valid_color_too_many_components),
		cmocka_unit_test(test_valid_color_out_of_range_high),
		cmocka_unit_test(test_valid_color_out_of_range_low),
		cmocka_unit_test(test_valid_color_boundary_zero),
		cmocka_unit_test(test_valid_color_boundary_max),
		cmocka_unit_test(test_valid_color_non_numeric),
		cmocka_unit_test(test_valid_color_empty_string),
		cmocka_unit_test(test_valid_coordinates_valid),
		cmocka_unit_test(test_valid_coordinates_valid_int_values),
		cmocka_unit_test(test_valid_coordinates_null),
		cmocka_unit_test(test_valid_coordinates_too_few),
		cmocka_unit_test(test_valid_coordinates_too_many),
		cmocka_unit_test(test_valid_coordinates_negative),
		cmocka_unit_test(test_valid_coordinates_without_decimal),
		cmocka_unit_test(test_valid_coordinates_decimal),
		cmocka_unit_test(test_valid_coordinates_non_numeric),
		cmocka_unit_test(test_valid_coordinates_numeric_with_non_numeric),
		cmocka_unit_test(test_valid_coordinates_empty_string),
		cmocka_unit_test(test_valid_normalized_vector_valid),
		cmocka_unit_test(test_valid_normalized_vector_null),
		cmocka_unit_test(test_valid_normalized_vector_empty),
		cmocka_unit_test(test_valid_normalized_vector_too_few),
		cmocka_unit_test(test_valid_normalized_vector_too_many),
		cmocka_unit_test(test_valid_normalized_vector_out_of_range),
		cmocka_unit_test(test_valid_normalized_vector_boundary_min),
		cmocka_unit_test(test_valid_normalized_vector_boundary_max),
		cmocka_unit_test(test_valid_normalized_vector_non_numeric),
		cmocka_unit_test(test_valid_fov_valid),
		cmocka_unit_test(test_valid_fov_null),
		cmocka_unit_test(test_valid_fov_empty),
		cmocka_unit_test(test_valid_fov_boundary_zero),
		cmocka_unit_test(test_valid_fov_boundary_max),
		cmocka_unit_test(test_valid_fov_out_of_range),
		cmocka_unit_test(test_valid_fov_negative),
		cmocka_unit_test(test_valid_fov_float),
		cmocka_unit_test(test_valid_fov_non_numeric),
		// Integration Tests
		cmocka_unit_test(test_valid_ambient_valid),
		cmocka_unit_test(test_valid_ambient_null_arr),
		cmocka_unit_test(test_valid_ambient_invalid_ratio),
		cmocka_unit_test(test_valid_ambient_invalid_color),
		cmocka_unit_test(test_valid_ambient_both_invalid),
		cmocka_unit_test(test_valid_ambient_boundary_ratio_zero),
		cmocka_unit_test(test_valid_ambient_boundary_ratio_one),
		cmocka_unit_test(test_valid_ambient_boundary_color_max),
		cmocka_unit_test(test_valid_camera_valid),
		cmocka_unit_test(test_valid_camera_null_arr),
		cmocka_unit_test(test_valid_camera_null_first_element),
		cmocka_unit_test(test_valid_camera_invalid_coordinates),
		cmocka_unit_test(test_valid_camera_invalid_vector),
		cmocka_unit_test(test_valid_camera_invalid_fov),
		cmocka_unit_test(test_valid_camera_all_invalid),
		cmocka_unit_test(test_valid_camera_boundary_fov_zero),
		cmocka_unit_test(test_valid_camera_boundary_fov_max),
		cmocka_unit_test(test_valid_camera_fov_out_of_range),
		cmocka_unit_test(test_valid_camera_vector_boundary),
		cmocka_unit_test(test_valid_camera_vector_non_numeric),
		cmocka_unit_test(test_valid_camera_fov_float),
		cmocka_unit_test(test_valid_camera_fov_negative),
		cmocka_unit_test(test_valid_light_valid),
		cmocka_unit_test(test_valid_light_null_arr),
		cmocka_unit_test(test_valid_light_null_first_element),
		cmocka_unit_test(test_valid_light_invalid_coordinates),
		cmocka_unit_test(test_valid_light_invalid_ratio),
		cmocka_unit_test(test_valid_light_invalid_color),
		cmocka_unit_test(test_valid_light_all_invalid),
		cmocka_unit_test(test_valid_light_boundary_ratio_zero),
		cmocka_unit_test(test_valid_light_boundary_ratio_one),
		cmocka_unit_test(test_valid_light_boundary_color_max),
		cmocka_unit_test(test_valid_light_ratio_above_one),
		cmocka_unit_test(test_valid_light_color_out_of_range),
		cmocka_unit_test(test_valid_light_coordinates_wrong_count),
		cmocka_unit_test(test_valid_light_null_coordinates),
		cmocka_unit_test(test_valid_sphere_valid),
		cmocka_unit_test(test_valid_sphere_null_arr),
		cmocka_unit_test(test_valid_sphere_invalid_coordinates),
		cmocka_unit_test(test_valid_sphere_invalid_diameter),
		cmocka_unit_test(test_valid_sphere_invalid_color),
		cmocka_unit_test(test_valid_sphere_all_invalid),
		cmocka_unit_test(test_valid_sphere_negative_diameter),
		cmocka_unit_test(test_valid_sphere_zero_diameter),
		cmocka_unit_test(test_valid_sphere_null_coordinates),
		cmocka_unit_test(test_valid_sphere_null_color),
		cmocka_unit_test(test_valid_plane_valid),
		cmocka_unit_test(test_valid_plane_null_arr),
		cmocka_unit_test(test_valid_plane_null_first_element),
		cmocka_unit_test(test_valid_plane_null_coordinates),
		cmocka_unit_test(test_valid_plane_null_vector),
		cmocka_unit_test(test_valid_plane_null_color),
		cmocka_unit_test(test_valid_plane_invalid_coordinates),
		cmocka_unit_test(test_valid_plane_invalid_vector),
		cmocka_unit_test(test_valid_plane_invalid_color),
		cmocka_unit_test(test_valid_plane_all_invalid),
		cmocka_unit_test(test_valid_plane_vector_out_of_range),
		cmocka_unit_test(test_valid_plane_vector_boundary_min),
		cmocka_unit_test(test_valid_plane_vector_boundary_max),
		cmocka_unit_test(test_valid_plane_color_boundary_zero),
		cmocka_unit_test(test_valid_plane_color_boundary_max),
		cmocka_unit_test(test_valid_plane_coordinates_wrong_count),
		cmocka_unit_test(test_valid_plane_vector_wrong_count),
		cmocka_unit_test(test_valid_cylinder_valid),
		cmocka_unit_test(test_valid_cylinder_null_arr),
		cmocka_unit_test(test_valid_cylinder_null_coordinates),
		cmocka_unit_test(test_valid_cylinder_null_vector),
		cmocka_unit_test(test_valid_cylinder_null_diameter),
		cmocka_unit_test(test_valid_cylinder_null_height),
		cmocka_unit_test(test_valid_cylinder_null_color),
		cmocka_unit_test(test_valid_cylinder_invalid_coordinates),
		cmocka_unit_test(test_valid_cylinder_invalid_vector),
		cmocka_unit_test(test_valid_cylinder_invalid_diameter),
		cmocka_unit_test(test_valid_cylinder_invalid_height),
		cmocka_unit_test(test_valid_cylinder_invalid_color),
		cmocka_unit_test(test_valid_cylinder_all_invalid),
		cmocka_unit_test(test_valid_cylinder_negative_diameter),
		cmocka_unit_test(test_valid_cylinder_zero_diameter),
		cmocka_unit_test(test_valid_cylinder_negative_height),
		cmocka_unit_test(test_valid_cylinder_zero_height),
		cmocka_unit_test(test_valid_cylinder_boundary_diameter),
		cmocka_unit_test(test_valid_cylinder_boundary_height),
		cmocka_unit_test(test_valid_cylinder_vector_out_of_range),
		cmocka_unit_test(test_valid_cylinder_vector_wrong_count),
		cmocka_unit_test(test_valid_cylinder_color_wrong_slot),
		// Input
		cmocka_unit_test(test_valid_input_valid_scene),
		cmocka_unit_test(test_valid_input_valid_scene_with_more_newline),
		cmocka_unit_test(test_valid_input_null_file),
		cmocka_unit_test(test_valid_input_invalid_extension),
		cmocka_unit_test(test_valid_input_no_extension),
		cmocka_unit_test(test_valid_input_missing_file),
		cmocka_unit_test(test_valid_input_empty_file),
		cmocka_unit_test(test_valid_input_missing_camera_and_light),
		cmocka_unit_test(test_valid_input_duplicate_ambient),
		cmocka_unit_test(test_valid_input_invalid_ambient),
		cmocka_unit_test(test_valid_input_missing_ambient_and_light),
		cmocka_unit_test(test_valid_input_duplicate_camera),
		cmocka_unit_test(test_valid_input_missing_ambient_and_camera),
		cmocka_unit_test(test_valid_input_duplicate_light),
		cmocka_unit_test(test_valid_input_valid_sphere),
		cmocka_unit_test(test_valid_input_invalid_sphere),
		cmocka_unit_test(test_valid_input_valid_plane),
		cmocka_unit_test(test_valid_input_invalid_plane),
		cmocka_unit_test(test_valid_input_valid_cylinder),
		cmocka_unit_test(test_valid_input_invalid_cylinder),
		cmocka_unit_test(test_valid_input_unknown_identifier),
	};
	printf("\n--- Validation Tests ---\n");
	return (cmocka_run_group_tests(tests, NULL, NULL));
}

static void	print_usage(void)
{
	printf("Usage: ./run_tests [OPTIONS]\n");
	printf("Options:\n");
	printf("  (no args)    Run all tests\n");
	printf("  validation   Run file validation tests only\n");
	printf("  -h, --help   Show this help message\n");
}

int	main(int argc, char *argv[])
{
	int	result;
	int	failed;

	if (argc > 1)
	{
		if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
		{
			print_usage();
			return (0);
		}
		if (strcmp(argv[1], "validation") == 0)
		{
			printf("\n=== Running validation Tests ===\n");
			return (run_validation_tests());
		}
		printf("Unknown option: %s\n", argv[1]);
		print_usage();
		return (1);
	}
	printf("\n=== Running Minishell Tests ===\n");
	failed = 0;
	result = run_validation_tests();
	if (result != 0)
		failed += result;
	printf("\n=== Test Suite Complete ===\n");
	if (failed > 0)
		printf("Total failures: %d\n", failed);
	else
		printf("All tests passed!\n");
	return (failed);
}
