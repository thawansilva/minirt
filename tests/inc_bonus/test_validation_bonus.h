
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_validation_bonus.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 10:00:00 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/22 20:23:42 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_VALIDATION_BONUS_H
# define TEST_VALIDATION_BONUS_H

/* cone */
void    test_valid_cone_valid(void **state);
void    test_valid_cone_invalid_coordinates(void **state);
void    test_valid_cone_invalid_diameter(void **state);
void    test_valid_cone_invalid_color(void **state);
void    test_valid_cone_negative_diameter(void **state);
void    test_valid_cone_zero_diameter(void **state);
void    test_valid_cone_null_coordinates(void **state);
void    test_valid_cone_null_diameter(void **state);
void    test_valid_cone_null_color(void **state);

/* hyperboloid */
void    test_valid_hyperboloid_valid(void **state);
void    test_valid_hyperboloid_invalid_coordinates(void **state);
void    test_valid_hyperboloid_invalid_vector(void **state);
void    test_valid_hyperboloid_invalid_color(void **state);
void    test_valid_hyperboloid_null_coordinates(void **state);
void    test_valid_hyperboloid_null_vector(void **state);
void    test_valid_hyperboloid_null_color(void **state);
void    test_valid_hyperboloid_vector_out_of_range(void **state);
void    test_valid_hyperboloid_vector_wrong_count(void **state);

/* paraboloid */
void    test_valid_paraboloid_valid(void **state);
void    test_valid_paraboloid_invalid_coordinates(void **state);
void    test_valid_paraboloid_invalid_vector(void **state);
void    test_valid_paraboloid_invalid_color(void **state);
void    test_valid_paraboloid_null_coordinates(void **state);
void    test_valid_paraboloid_null_vector(void **state);
void    test_valid_paraboloid_null_color(void **state);
void    test_valid_paraboloid_vector_out_of_range(void **state);
void    test_valid_paraboloid_vector_wrong_count(void **state);

/* is_valid_input bonus — integration */
void    test_valid_input_bonus_valid_full_scene(void **state);
void    test_valid_input_bonus_valid_cone(void **state);
void    test_valid_input_bonus_valid_hyperboloid(void **state);
void    test_valid_input_bonus_valid_paraboloid(void **state);
void    test_valid_input_bonus_invalid_cone(void **state);
void    test_valid_input_bonus_invalid_hyperboloid(void **state);
void    test_valid_input_bonus_invalid_paraboloid(void **state);
void    test_valid_input_bonus_multiple_cones(void **state);
void    test_valid_input_bonus_multiple_hyperboloids(void **state);
void    test_valid_input_bonus_multiple_paraboloids(void **state);
void    test_valid_input_bonus_any_order(void **state);
#endif
