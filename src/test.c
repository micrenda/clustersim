/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */

#include <check.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "common.h"

int double_eq(double d1, double d2, double margin);
CommonStatus* create_test_status_sized(unsigned short dimensions, unsigned int size);
CommonStatus* create_test_status(unsigned short dimensions);



START_TEST (test_init_2d)
{
    unsigned short dimensions = 2;

    unsigned int space_sizes[dimensions];
    space_sizes[0] = 300;
    space_sizes[1] = 200;

    CommonStatus* status = init_common(dimensions, space_sizes, 100, 0);

    ck_assert_int_eq(status->cartesian_moltiplicators[0], 200);
    ck_assert_int_eq(status->cartesian_moltiplicators[1],   1);


    ck_assert_int_eq(status->polar_moltiplicators[1][0],     1);
    ck_assert_int_eq(status->polar_moltiplicators[10][0],    1);
    ck_assert_int_eq(status->polar_moltiplicators[100][0],   1);

    free_common(status);
}
END_TEST

START_TEST (test_init_3d)
{
    unsigned short dimensions = 3;

    unsigned int space_sizes[dimensions];
    space_sizes[0] = 300;
    space_sizes[1] = 200;
    space_sizes[2] = 100;


    CommonStatus* status = init_common(dimensions, space_sizes, 100, 0);

    ck_assert_int_eq(status->cartesian_moltiplicators[0], 200*100);
    ck_assert_int_eq(status->cartesian_moltiplicators[1],     100);
    ck_assert_int_eq(status->cartesian_moltiplicators[2],       1);


    unsigned int radius;
    unsigned int expected_0;

    radius = 1;
    expected_0 = floor(2.d * M_PI / min_polar_angle(radius));
    ck_assert_int_eq(status->polar_moltiplicators[radius][0],   expected_0);
    ck_assert_int_eq(status->polar_moltiplicators[radius][1],   1);

    radius = 10;
    expected_0 = floor(2.d * M_PI / min_polar_angle(radius));
    ck_assert_int_eq(status->polar_moltiplicators[radius][0],   expected_0);
    ck_assert_int_eq(status->polar_moltiplicators[radius][1],   1);

    radius = 100;
    expected_0 = floor(2.d * M_PI / min_polar_angle(radius));
    ck_assert_int_eq(status->polar_moltiplicators[radius][0],   expected_0);
    ck_assert_int_eq(status->polar_moltiplicators[radius][1],   1);

    free_common(status);
}
END_TEST

START_TEST (test_init_4d)
{
    unsigned short dimensions = 4;

    unsigned int space_sizes[dimensions];
    space_sizes[0] = 300;
    space_sizes[1] = 200;
    space_sizes[2] = 100;
    space_sizes[3] = 50;

    CommonStatus* status = init_common(dimensions, space_sizes, 100, 0);


    ck_assert_int_eq(status->cartesian_moltiplicators[0],  200*100*50);
    ck_assert_int_eq(status->cartesian_moltiplicators[1],      100*50);
    ck_assert_int_eq(status->cartesian_moltiplicators[2],          50);
    ck_assert_int_eq(status->cartesian_moltiplicators[3],           1);

    free_common(status);
}
END_TEST

START_TEST (test_add_relative_vector)
{
    unsigned short dimensions = 6;

    CommonStatus* status = create_test_status(dimensions);

    unsigned int a[dimensions];
    a[0] = 0;
    a[1] = 1;
    a[2] = 2;
    a[3] = 3;
    a[4] = 4;
    a[5] = 5;

    int b[dimensions];
    b[0] =  0;
    b[1] = -1;
    b[2] =  1;
    b[3] = -2;
    b[4] =  2;
    b[5] = -3;

    unsigned int c[dimensions];

    add_relative_vector(status, c, a, b);

    ck_assert_int_eq(c[0], 0);
    ck_assert_int_eq(c[1], 0);
    ck_assert_int_eq(c[2], 3);
    ck_assert_int_eq(c[3], 1);
    ck_assert_int_eq(c[4], 6);
    ck_assert_int_eq(c[5], 2);

    free_common(status);

}
END_TEST

START_TEST (test_encode_position_cartesian_2d)
{

    unsigned short dimensions = 2;
    unsigned int space_sizes[dimensions];

    space_sizes[0] = 300;
    space_sizes[1] = 200;

    CommonStatus* status = init_common(dimensions, space_sizes, 100, 0);

    unsigned int coordinates[dimensions];
    coordinates[0] = 35;
    coordinates[1] = 45;

    unsigned long encoded = encode_position_cartesian(status, coordinates);

    ck_assert_int_eq(encoded, 35 * 200 + 45);

    free_common(status);

}
END_TEST

START_TEST (test_encode_position_cartesian_3d)
{

    unsigned short dimensions = 3;
    unsigned int space_sizes[dimensions];

    space_sizes[0] = 300;
    space_sizes[1] = 200;
    space_sizes[2] = 100;

    CommonStatus* status = init_common(dimensions, space_sizes, 100, 0);

    unsigned int coordinates[dimensions];
    coordinates[0] = 35;
    coordinates[1] = 45;
    coordinates[2] = 55;

    unsigned long encoded = encode_position_cartesian(status, coordinates);

    ck_assert_int_eq(encoded, 35 * 200 * 100 + 45 * 100 + 55);

    free_common(status);

}
END_TEST

START_TEST (test_encode_position_cartesian_4d)
{

    unsigned short dimensions = 4;
    unsigned int space_sizes[dimensions];

    space_sizes[0] = 300;
    space_sizes[1] = 200;
    space_sizes[2] = 100;
    space_sizes[3] = 50;

    CommonStatus* status = init_common(dimensions, space_sizes, 100, 0);

    unsigned int coordinates[dimensions];
    coordinates[0] = 35;
    coordinates[1] = 45;
    coordinates[2] = 55;
    coordinates[3] = 65;

    unsigned long encoded = encode_position_cartesian(status, coordinates);

    ck_assert_int_eq(encoded, 35 * 200 * 100 * 50 + 45 * 100 * 50 + 55 * 50 + 65);

    free_common(status);

}
END_TEST


START_TEST (test_decode_position_cartesian_2d)
{

    unsigned short dimensions = 2;

    unsigned int space_sizes[dimensions];
    space_sizes[0] = 300;
    space_sizes[1] = 200;

    CommonStatus* status = init_common(dimensions, space_sizes, 100, 0);

    unsigned long encoded = 35 * 200 + 45;
    unsigned int coordinates[dimensions];


    decode_position_cartesian(status, coordinates, encoded);

    ck_assert_int_eq(coordinates[0], 35);
    ck_assert_int_eq(coordinates[1], 45);

    free_common(status);
}
END_TEST

START_TEST (test_decode_position_cartesian_3d)
{

    unsigned short dimensions = 3;

    unsigned int space_sizes[dimensions];
    space_sizes[0] = 300;
    space_sizes[1] = 200;
    space_sizes[2] = 100;

    CommonStatus* status = init_common(dimensions, space_sizes, 100, 0);

    unsigned long encoded = 35 * 200 * 100 + 45 * 100 + 55;
    unsigned int coordinates[dimensions];

    decode_position_cartesian(status, coordinates, encoded);

    ck_assert_int_eq(coordinates[0], 35);
    ck_assert_int_eq(coordinates[1], 45);
    ck_assert_int_eq(coordinates[2], 55);

    free_common(status);
}
END_TEST

START_TEST (test_decode_position_cartesian_4d)
{

    unsigned short dimensions = 4;

    unsigned int space_sizes[dimensions];
    space_sizes[0] = 300;
    space_sizes[1] = 200;
    space_sizes[2] = 100;
    space_sizes[3] =  50;

    CommonStatus* status = init_common(dimensions, space_sizes, 100, 0);

    unsigned long encoded =  35 * 200 * 100 * 50 + 45 * 100 * 50 + 55 * 50 + 15;
    unsigned int coordinates[dimensions];


    decode_position_cartesian(status, coordinates, encoded);

    ck_assert_int_eq(coordinates[0], 35);
    ck_assert_int_eq(coordinates[1], 45);
    ck_assert_int_eq(coordinates[2], 55);
    ck_assert_int_eq(coordinates[3], 15);

    free_common(status);
}
END_TEST


START_TEST (test_dimension_to_label)
{
    char axis_label[8];

    CommonStatus* status1 = create_test_status(1);
    dimension_to_label(axis_label, status1, 0);
    ck_assert_str_eq(axis_label, "x");
    free_common(status1);


    CommonStatus* status2 = create_test_status(2);
    dimension_to_label(axis_label, status2, 0);
    ck_assert_str_eq(axis_label, "x");
    dimension_to_label(axis_label, status2, 1);
    ck_assert_str_eq(axis_label, "y");
    free_common(status2);


    CommonStatus* status3 = create_test_status(3);
    dimension_to_label(axis_label, status3, 0);
    ck_assert_str_eq(axis_label, "x");
    dimension_to_label(axis_label, status3, 1);
    ck_assert_str_eq(axis_label, "y");
    dimension_to_label(axis_label, status3, 2);
    ck_assert_str_eq(axis_label, "z");
    free_common(status3);


    CommonStatus* status4 = create_test_status(4);
    dimension_to_label(axis_label, status4, 0);
    ck_assert_str_eq(axis_label, "r1");
    dimension_to_label(axis_label, status4, 1);
    ck_assert_str_eq(axis_label, "r2");
    dimension_to_label(axis_label, status4, 2);
    ck_assert_str_eq(axis_label, "r3");
    dimension_to_label(axis_label, status4, 3);
    ck_assert_str_eq(axis_label, "r4");
    free_common(status4);


    CommonStatus* status5 = create_test_status(5);
    dimension_to_label(axis_label, status5, 0);
    ck_assert_str_eq(axis_label, "r1");
    dimension_to_label(axis_label, status5, 1);
    ck_assert_str_eq(axis_label, "r2");
    dimension_to_label(axis_label, status5, 2);
    ck_assert_str_eq(axis_label, "r3");
    dimension_to_label(axis_label, status5, 3);
    ck_assert_str_eq(axis_label, "r4");
    dimension_to_label(axis_label, status5, 4);
    ck_assert_str_eq(axis_label, "r5");
    free_common(status5);
}
END_TEST

START_TEST (test_label_to_dimensions)
{
    CommonStatus* status1 = create_test_status(1);
    ck_assert_int_eq(label_to_dimension(status1, "x"), 0);
    free_common(status1);

    CommonStatus* status2 = create_test_status(2);
    ck_assert_int_eq(label_to_dimension(status2, "x"), 0);
    ck_assert_int_eq(label_to_dimension(status2, "y"), 1);
    free_common(status2);

    CommonStatus* status3 = create_test_status(3);
    ck_assert_int_eq(label_to_dimension(status3, "x"), 0);
    ck_assert_int_eq(label_to_dimension(status3, "y"), 1);
    ck_assert_int_eq(label_to_dimension(status3, "z"), 2);
    free_common(status3);

    CommonStatus* status4 = create_test_status(4);
    ck_assert_int_eq(label_to_dimension(status4, "r1"), 0);
    ck_assert_int_eq(label_to_dimension(status4, "r2"), 1);
    ck_assert_int_eq(label_to_dimension(status4, "r3"), 2);
    ck_assert_int_eq(label_to_dimension(status4, "r4"), 3);
    free_common(status4);

    CommonStatus* status5 = create_test_status(5);
    ck_assert_int_eq(label_to_dimension(status5, "r1"), 0);
    ck_assert_int_eq(label_to_dimension(status5, "r2"), 1);
    ck_assert_int_eq(label_to_dimension(status5, "r3"), 2);
    ck_assert_int_eq(label_to_dimension(status5, "r4"), 3);
    ck_assert_int_eq(label_to_dimension(status5, "r5"), 4);
    free_common(status5);
}
END_TEST


START_TEST (test_min_polar_angle)
{
    ck_assert(double_eq(min_polar_angle(1),      1.0471975511966,        0.00000001));
    ck_assert(double_eq(min_polar_angle(2),      0.505360510284157,      0.00000001));
    ck_assert(double_eq(min_polar_angle(5),      0.20033484232312,       0.00000001));
    ck_assert(double_eq(min_polar_angle(10),     0.10004171361154,       0.00000001));
    ck_assert(double_eq(min_polar_angle(15),     0.0666790185226044,     0.00000001));
    ck_assert(double_eq(min_polar_angle(20),     0.0500052097987217,     0.00000001));
    ck_assert(double_eq(min_polar_angle(75),     0.0133334321007428,     0.00000001));
    ck_assert(double_eq(min_polar_angle(100),    0.0100000416671349,     0.00000001));
    ck_assert(double_eq(min_polar_angle(15000),  0.0000666666661063556,  0.00000001));
    ck_assert(double_eq(min_polar_angle(50000),  0.000020000000827737,   0.00000001));

}
END_TEST


START_TEST (test_encode_position_polar_2d)
{
    CommonStatus* status = create_test_status_sized(2, 100);

    unsigned int radius = 75;

    double min_angle = min_polar_angle(radius);
    ck_assert(double_eq(min_angle,     0.0133334321007428,     0.00000001));

    double coordinates[status->dimensions - 1];
    coordinates[0] = M_PI * 0.5d;

    unsigned long encoded   = encode_position_polar(status, coordinates,  radius);
    unsigned long expected  = floor(M_PI * 0.5d / min_angle);

    ck_assert_int_eq(encoded, expected);

    free_common(status);

}
END_TEST


START_TEST (test_encode_position_polar_3d)
{

    CommonStatus* status = create_test_status_sized(3, 100);

    unsigned int radius = 75;

    double min_angle = min_polar_angle(radius);
    ck_assert(double_eq(min_angle,     0.0133334321007428,     0.00000001));

    double coordinates[status->dimensions - 1];
    coordinates[0] = M_PI * 0.3d;
    coordinates[1] = M_PI * 1.5d;

    unsigned long encoded  = encode_position_polar(status, coordinates,  radius);
    unsigned long expected = floor(M_PI * 0.3d / min_angle) * floor(2.d * M_PI / min_angle) + floor(M_PI * 1.5d / min_angle);

    ck_assert_int_eq(encoded,  expected);

    free_common(status);

}
END_TEST

START_TEST (test_encode_position_polar_4d)
{

    CommonStatus* status = create_test_status_sized(4, 100);

    unsigned int radius = 75;

    double min_angle = min_polar_angle(radius);
    ck_assert(double_eq(min_angle,     0.0133334321007428,     0.00000001));

    double coordinates[status->dimensions - 1];
    coordinates[0] = M_PI * 0.3d;
    coordinates[1] = M_PI * 0.7d;
    coordinates[2] = M_PI * 1.8d;

    unsigned long encoded  = encode_position_polar(status, coordinates,  radius);
    unsigned long expected =
        floor(M_PI * 0.3d / min_angle) * floor(1.d * M_PI / min_angle) * floor(2.d * M_PI / min_angle) +
        floor(M_PI * 0.7d / min_angle) * floor(2.d * M_PI / min_angle) +
        floor(M_PI * 1.8d / min_angle);

    ck_assert_int_eq(encoded,  expected);

    free_common(status);

}
END_TEST

START_TEST (test_decode_position_polar_2d)
{
    CommonStatus* status = create_test_status_sized(2, 100);

    unsigned int radius = 75;

    double min_angle = min_polar_angle(radius);
    ck_assert(double_eq(min_angle,     0.0133334321007428,     0.00000001));

    unsigned long encoded = floor(M_PI * 0.5d / min_angle);

    double coordinates[status->dimensions - 1];

    decode_position_polar(status, coordinates, radius, encoded);

    ck_assert(double_eq(coordinates[0], 1.560012, 0.000001)); // It is not equals to M_PI * 0.5d due to discretization

    free_common(status);
}
END_TEST

START_TEST (test_decode_position_polar_3d)
{
    CommonStatus* status = create_test_status_sized(3, 100);

    unsigned int radius = 75;

    double min_angle = min_polar_angle(radius);
    ck_assert(double_eq(min_angle,     0.0133334321007428,     0.00000001));

    unsigned long encoded = floor(M_PI * 0.7d / min_angle) * floor(2.d * M_PI / min_angle) + floor(M_PI * 0.5d / min_angle);

    double coordinates[status->dimensions - 1];

    decode_position_polar(status, coordinates, radius, encoded);

    ck_assert(double_eq(coordinates[0], 2.186683, 0.000001)); // It is not equals to M_PI * 0.7d due to discretization
    ck_assert(double_eq(coordinates[1], 1.560012, 0.000001)); // It is not equals to M_PI * 0.5d due to discretization

    free_common(status);
}
END_TEST

START_TEST (test_decode_position_polar_4d)
{
    CommonStatus* status = create_test_status_sized(4, 100);

    unsigned int radius = 75;

    double min_angle = min_polar_angle(radius);
    ck_assert(double_eq(min_angle,     0.0133334321007428,     0.00000001));

    unsigned long encoded =
        floor(M_PI * 0.9d / min_angle) * floor(1.d * M_PI / min_angle) * floor(2.d * M_PI / min_angle) +
        floor(M_PI * 0.7d / min_angle) * floor(2.d * M_PI / min_angle) +
        floor(M_PI * 0.5d / min_angle);

    double coordinates[status->dimensions - 1];

    decode_position_polar(status, coordinates, radius, encoded);

    ck_assert(double_eq(coordinates[0], 2.826688, 0.000001)); // It is not equals to M_PI * 0.9d due to discretization
    ck_assert(double_eq(coordinates[1], 2.186683, 0.000001)); // It is not equals to M_PI * 0.7d due to discretization
    ck_assert(double_eq(coordinates[2], 1.560012, 0.000001)); // It is not equals to M_PI * 0.5d due to discretization

    free_common(status);
}
END_TEST


START_TEST (test_calculate_distance)
{
    CommonStatus* status = create_test_status_sized(4, 5000);

    unsigned int point_0[status->dimensions];
    point_0[0] = 0;
    point_0[1] = 0;
    point_0[2] = 0;
    point_0[3] = 0;

    unsigned int point_a[status->dimensions];
    point_a[0] = 30;
    point_a[1] = 120;
    point_a[2] = 90;
    point_a[3] = 0;

    unsigned int point_b[status->dimensions];
    point_b[0] = 130;
    point_b[1] = 0;
    point_b[2] = 15;
    point_b[3] = 900;



    unsigned int distance_aa = calculate_distance(status, point_a, point_a);
    ck_assert_int_eq(distance_aa, 0);

    unsigned int distance_bb = calculate_distance(status, point_b, point_b);
    ck_assert_int_eq(distance_bb, 0);

    unsigned int distance_0a = calculate_distance(status, point_0, point_a);
    ck_assert_int_eq(distance_0a, 153);

    unsigned int distance_0b = calculate_distance(status, point_0, point_b);
    ck_assert_int_eq(distance_0b, 909);

    unsigned int distance_ab = calculate_distance(status, point_a, point_b);
    ck_assert_int_eq(distance_ab, 917);

    free_common(status);
}
END_TEST

START_TEST (test_cartesian_to_polar)
{
    CommonStatus* status = create_test_status_sized(3, 1000);


    unsigned int point[status->dimensions];
    point[0] = 30;
    point[1] = 120;
    point[2] = 90;

    double angles[status->dimensions-1];

    convert_cartesian_to_polar_angles(status, angles, point);

    // [0,π)
    double expected_0   = atan(sqrt(120.d*120.d+90.d*90.d)/30.d);
    // [0,2π)
    double expected_1   = atan(90.d/120.d);

    ck_assert(double_eq(angles[0], expected_0, 0.000001));
    ck_assert(double_eq(angles[1], expected_1, 0.000001));

    free_common(status);
}
END_TEST


START_TEST (test_polar_to_cartesian)
{
    CommonStatus* status = create_test_status_sized(3, 1000);

    double angles[status->dimensions-1];
    angles[0]   = atan(sqrt(120.d*120.d+90.d*90.d)/30.d);// [0,π)
    angles[1]   = atan(90.d/120.d); // [0,2π)

    unsigned int radius = round(sqrt(30*30+120*120+90*90));

    int point[status->dimensions];

    convert_polar_angles_to_cartesian(status, angles, radius, point);

    ck_assert_int_eq(point[0], 30);
    ck_assert_int_eq(point[1], 120);
    ck_assert_int_eq(point[2], 90);

    free_common(status);
}
END_TEST


START_TEST (test_neighbours_2d_init)
{
    unsigned short dimensions = 2;

    unsigned int space_sizes[dimensions];
    space_sizes[0] = 300;
    space_sizes[1] = 200;

    CommonStatus* status = init_common(dimensions, space_sizes, 100, 0);
    
    SpacePixel* space = malloc(status->space_volume * sizeof(SpacePixel));
    init_space(status, space);
    
    
    unsigned int point[status->dimensions];
    unsigned int encoded;
    
    // Corners
    point[0] = 0; point[1] = 0;
    encoded = encode_position_cartesian(status, point);
    ck_assert_int_eq(space[encoded].fill_neighbours, 5);

    point[0] = 299; point[1] = 0;
    encoded = encode_position_cartesian(status, point);
    ck_assert_int_eq(space[encoded].fill_neighbours, 5);
    
    point[0] = 0; point[1] = 199;
    encoded = encode_position_cartesian(status, point);
    ck_assert_int_eq(space[encoded].fill_neighbours, 5);
    
    point[0] = 299; point[1] = 199;
    encoded = encode_position_cartesian(status, point);
    ck_assert_int_eq(space[encoded].fill_neighbours, 5);   
    
        point[0] = 0; point[1] = 0;
    encoded = encode_position_cartesian(status, point);
    ck_assert_int_eq(space[encoded].fill_neighbours, 5);


	// Mid sides
    point[0] = 0; point[1] = 99;
    encoded = encode_position_cartesian(status, point);
    ck_assert_int_eq(space[encoded].fill_neighbours, 3);
    
    point[0] = 299; point[1] = 99;
    encoded = encode_position_cartesian(status, point);
    ck_assert_int_eq(space[encoded].fill_neighbours, 3);
    
    point[0] = 149; point[1] = 199;
    encoded = encode_position_cartesian(status, point);
    ck_assert_int_eq(space[encoded].fill_neighbours, 3);
    
    point[0] = 149; point[1] = 199;
    encoded = encode_position_cartesian(status, point);
    ck_assert_int_eq(space[encoded].fill_neighbours, 3);  
    
    // Center
    point[0] = 10; point[1] = 10;
    encoded = encode_position_cartesian(status, point);
    ck_assert_int_eq(space[encoded].fill_neighbours, 0);
    
    point[0] = 200; point[1] = 50;
    encoded = encode_position_cartesian(status, point);
    ck_assert_int_eq(space[encoded].fill_neighbours, 0);
    
    point[0] = 40; point[1] = 198;
    encoded = encode_position_cartesian(status, point);
    ck_assert_int_eq(space[encoded].fill_neighbours, 0);
    
    point[0] = 30; point[1] = 150;
    encoded = encode_position_cartesian(status, point);
    ck_assert_int_eq(space[encoded].fill_neighbours, 0); 
     
    
	free(space);
    free_common(status);
}
END_TEST


Suite * general_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("General Suite");

    /* Core test case */
    tc_core = tcase_create("Common module");


    tcase_add_test(tc_core, test_add_relative_vector);

    tcase_add_test(tc_core, test_init_2d);
    tcase_add_test(tc_core, test_init_3d);
    tcase_add_test(tc_core, test_init_4d);

    tcase_add_test(tc_core, test_encode_position_cartesian_2d);
    tcase_add_test(tc_core, test_encode_position_cartesian_3d);
    tcase_add_test(tc_core, test_encode_position_cartesian_4d);

    tcase_add_test(tc_core, test_decode_position_cartesian_2d);
    tcase_add_test(tc_core, test_decode_position_cartesian_3d);
    tcase_add_test(tc_core, test_decode_position_cartesian_4d);

    tcase_add_test(tc_core, test_dimension_to_label);
    tcase_add_test(tc_core, test_label_to_dimensions);

    tcase_add_test(tc_core, test_min_polar_angle);

    tcase_add_test(tc_core, test_encode_position_polar_2d);
    tcase_add_test(tc_core, test_encode_position_polar_3d);
    tcase_add_test(tc_core, test_encode_position_polar_4d);

    tcase_add_test(tc_core, test_decode_position_polar_2d);
    tcase_add_test(tc_core, test_decode_position_polar_3d);
    tcase_add_test(tc_core, test_decode_position_polar_4d);

    tcase_add_test(tc_core, test_calculate_distance);

    tcase_add_test(tc_core, test_cartesian_to_polar);
    tcase_add_test(tc_core, test_polar_to_cartesian);
    
    tcase_add_test(tc_core, test_neighbours_2d_init);

    suite_add_tcase(s, tc_core);

    return s;
}

int test_everything()
{

    int number_failed;

    Suite *s    = general_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int double_eq(double d1, double d2, double margin)
{
   return fabs(d1 - d2) < margin;
}


CommonStatus* create_test_status_sized(unsigned short dimensions, unsigned int size)
{
    unsigned int space_sizes[dimensions];
    for (unsigned short d = 0; d < dimensions; d++)
        space_sizes[d] = size;

    return init_common(dimensions, space_sizes, 200, 0);
}

CommonStatus* create_test_status(unsigned short dimensions)
{
    return create_test_status_sized(dimensions, 100);
}
