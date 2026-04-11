/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 08:54:40 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/11 15:16:32 by thaperei         ###   ########.fr       */
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
		cmocka_unit_test(test_valid_normal),
		cmocka_unit_test(test_invalid_normal),
		cmocka_unit_test(test_valid_fov),
		cmocka_unit_test(test_invalid_fov),
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
