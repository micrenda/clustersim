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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include "common.h"



CommonStatus* init_common(unsigned short dimensions, unsigned int space_sizes[dimensions], unsigned int duration)
{
    CommonStatus* status = calloc(1, sizeof(CommonStatus));

    status->dimensions = dimensions;
    status->space_sizes = space_sizes;

    status->space_volume = 1;
    for (unsigned short d = 0; d < status->dimensions; ++d)
    {
        status->space_volume *= space_sizes[d];
    }


    status->cartesian_moltiplicators = calloc(dimensions, sizeof(unsigned long));

    // Building cartesian_moltiplicators
    for (unsigned short d = 0; d < status->dimensions; ++d)
    {
        unsigned int moltiplicator = 1;
        for (unsigned short e = d + 1; e < status->dimensions; ++e)
        {
            moltiplicator *= space_sizes[e];
        }
        status->cartesian_moltiplicators[d] = moltiplicator;
    }

    // Determining the max_radius of a cluster
    status->max_radius = 0;
    for (unsigned short d = 0; d < status->dimensions; ++d)
    {
        if (space_sizes[d] > status->max_radius)
            status->max_radius = space_sizes[d];
    }

    // Building min_surface_angles for every radius (up to max_radius)
    status->min_polar_angles = calloc(status->max_radius+1, sizeof(double));
    status->min_polar_angles[0] = 0;
    for (unsigned int radius = 1; radius <= status->max_radius; ++radius)
    {
        status->min_polar_angles[radius] = min_polar_angle(radius);
    }


    //Building polar_moltiplicators
    status->polar_moltiplicators = calloc(status->max_radius+1, sizeof(unsigned int*));

    status->polar_moltiplicators[0] = calloc(dimensions-1, sizeof(unsigned int));
    for (unsigned int radius = 1; radius <= status->max_radius; ++radius)
    {
        status->polar_moltiplicators[radius] = calloc(status->dimensions-1, sizeof(unsigned int));
        for (unsigned short d = 0; d < status->dimensions - 1; ++d)
        {
            unsigned int moltiplicator = 1;
            for (unsigned short e = d + 1; e < status->dimensions - 1; ++e)
                moltiplicator *=  (unsigned int) floor((e == status->dimensions - 2 ? 2.d * M_PI : M_PI) / status->min_polar_angles[radius]);

            status->polar_moltiplicators[radius][d] = moltiplicator;
        }
    }

    status->stat_pixel_grow = calloc(duration, sizeof(unsigned int));
    status->stat_pixel_grow_total = 0;


    // Adjacent arrays map
    short base[] = {-1, 0 , +1};
    status->adjacents_count = calculate_direction_combinations_count(status, 3);
    status->adjacents = calloc(status->adjacents_count, sizeof(int*));
    for (unsigned int i = 0; i < status->adjacents_count; i++)
        status->adjacents[i] = calloc(dimensions, sizeof(int));

    calculate_direction_combinations(status, 3, base);


    return status;
}


// Given a set of catresian coordinates, it return an unsigned int that can be used to access the space array
unsigned long encode_position_cartesian(CommonStatus* status, unsigned int coordinates[status->dimensions])
{

    unsigned long encoded_position = 0;

    for (unsigned short d = 0; d < status->dimensions; ++d)
    {
        encoded_position += coordinates[d] * status->cartesian_moltiplicators[d];
    }

    return encoded_position;
}


// Given an encoded position, it fills the coordinates array with the cartesian coordinate of the position
void decode_position_cartesian(CommonStatus* status, unsigned int coordinates[status->dimensions], unsigned long encoded_position)
{
    for (unsigned short d = 0; d < status->dimensions; ++d)
    {
        unsigned long buffer = encoded_position;

        if (d > 0)
            buffer %= status->cartesian_moltiplicators[d-1];

        coordinates[d] = buffer / status->cartesian_moltiplicators[d];
    }
}


// Given a set of polar angles, it return an unsigned int reppresenting this array
unsigned long encode_position_polar(CommonStatus* status, double angles[status->dimensions-1], unsigned int radius)
{
    unsigned long encoded_position = 0;

    for (unsigned short d = 0; d < status->dimensions - 1; ++d)
    {
        encoded_position += floor(status->polar_moltiplicators[radius][d] * floor(angles[d] / status->min_polar_angles[radius]));
    }



    return encoded_position;
}


// Given an encoded position, it fills the coordinates array with the polar coordinate of the position
void decode_position_polar(CommonStatus* status, double angles[status->dimensions-1], unsigned int radius, unsigned long encoded_position)
{
    unsigned long buffer = encoded_position;

    for (unsigned short d = 0; d < status->dimensions - 1; ++d)
    {
        unsigned int moltiplicator = status->polar_moltiplicators[radius][d];
        angles[d] = (buffer / moltiplicator) *  status->min_polar_angles[radius];
        buffer %= moltiplicator;
    }
}



// Polar coordinates in N dimension means that we can represents any point of the space with N dimensions with these informations
// r    - distance from the origin and the center
// ϕ1,ϕ2,ϕ3 ... ϕ(N-1)
// where all the ϕ ∈ [0,π) but ϕN-1 ∈ [0,2π)
//
// ϕ1 = arctan( √(x2² + x3² + ... + xN²) / x1 )
// ϕ2 = arctan( √(x3² + ... + xN²) / x2 )
// ϕ3 = arctan( √(x4² + ... + xN²) / x3 )
// ...
// ϕ(N-1) = arctan( √(xN²) / x(N-1) )
//

void convert_cartesian_to_polar_angles(CommonStatus* status, double angles[status->dimensions-1], unsigned int coordinates[status->dimensions])
{
    for (unsigned short d = 0; d < status->dimensions - 1; d++)
    {
        unsigned int buffer = 0;

        for (unsigned short e = d + 1; e < status->dimensions; ++e)
            buffer += coordinates[e] * coordinates[e];

        angles[d] = atan(sqrt(buffer) / coordinates[d]);
    }
}

// x1 = r cos(ϕ1)
// x2 = r sin(ϕ1) cos(ϕ2)
// x3 = r sin(ϕ1) sin(ϕ2) cos(ϕ3)
// ...
// xn-1 = r sin(ϕ1) sin(ϕ2) sin(ϕ3) ... cos(ϕn-1)
// xn   = r sin(ϕ1) sin(ϕ2) sin(ϕ3) ... sin(ϕn-1)
//
void convert_polar_angles_to_cartesian(CommonStatus* status, double angles[status->dimensions-1], unsigned int radius, int coordinates[status->dimensions])
{
    for (unsigned short d = 0; d < status->dimensions; d++)
    {
        double buffer = radius;

        for (unsigned short e = 0; e < d; e++)
        {
            buffer *= sin(angles[e]);
        }

        if (d < status->dimensions - 1)
        {
            buffer *= cos(angles[d]);
        }

        coordinates[d] = (int) floor(buffer);
    }

}

// We know that the minimum distance between two pixel in the surface is equals to the side of the pixel (we assume 1)
// we need to know for a given radius, which is the minimum angle between two pixel in the same surface.
//
// We image that we have a isoscele triangle with two sides long radius and the short side long 1 (the min distance between two pixels).
// Using the Carnot theorem:
// a² = b² + c² -2bc cos(α)
//
// we can extract α:
// α = arcos( (b²+c²-a²)/(2bc))
//
// In our case b = c = radius while a is the min distance = 1

double min_polar_angle(unsigned int radius)
{
    return acos( (2.d  * radius * radius - 1.d) / (2.d * radius * radius)) / 3.d;
}

// Calculate the distance between two points
unsigned int calculate_distance(CommonStatus* status, unsigned int point1[status->dimensions], unsigned int point2[status->dimensions])
{
    unsigned int distance_pow2 = 0;

    for (unsigned short d = 0; d < status->dimensions; d++)
    {
        distance_pow2 += (point2[d] - point1[d]) * (point2[d] - point1[d]);
    }

    return floor(sqrt(distance_pow2));
}

unsigned int get_surface_points_count(CommonStatus* status, unsigned int radius)
{
    unsigned int count = 1;

    for (unsigned short d = 0; d < status->dimensions - 2; d++)
        count *= M_PI / status->min_polar_angles[radius];

    count *= 2.d * M_PI / status->min_polar_angles[radius];

    return count;
}

void dimension_to_label(char dest[8], CommonStatus* status, unsigned short d)
{
    if (d >= status->dimensions)
    {
        strcpy(dest, "?");
        return;
    }


    if (status->dimensions <= 3)
    {
        switch (d)
        {
        case 0:
            strcpy(dest, "x");
            return;
        case 1:
            strcpy(dest, "y");
            return;
        case 2:
            strcpy(dest, "z");
            return;
        case 3:
            strcpy(dest, "?");
            return;
        }
    }
    else
    {
        sprintf(dest, "r%d", d+1);
        return;
    }
}

unsigned short label_to_dimension(CommonStatus* status, char* label)
{
    if (status->dimensions >= 1 && status->dimensions <= 3)
    {
        if (strcmp(label, "x") == 0)
            return 0;
    }

    if (status->dimensions >= 2 && status->dimensions <= 3)
    {
        if (strcmp(label, "y") == 0)
            return 1;
    }

    if (status->dimensions >= 3 && status->dimensions <= 3)
    {
        if (strcmp(label, "z") == 0)
            return 2;
    }


    if (status->dimensions > 3)
    {
        char s[10];
        for (unsigned short d = 0; d < status->dimensions; d++)
        {
            sprintf(s, "r%d", d+1);
            if (strcmp(label, s) == 0)
                return d;
        }
    }

    printf("ERROR - Unable to decode axis '%s' in a %uD system (up to 3D systems use: x,y,z. For 4D+ systems use: r1,r2,r3,r4...)\n", label, status->dimensions);
    exit(-1);

    return USHRT_MAX; // If no corrispondence is found
}

void free_common(CommonStatus* status)
{
    free(status->cartesian_moltiplicators);
    free(status->min_polar_angles);

    for (unsigned int r = 0; r < status->max_radius + 1; r++)
        free(status->polar_moltiplicators[r]);
    free(status->polar_moltiplicators);

    free(status->stat_pixel_grow);

    for (unsigned int i = 0; i < status->adjacents_count; i++)
        free(status->adjacents[i]);
    free(status->adjacents);

    free(status);

}
unsigned int calculate_direction_combinations_count(CommonStatus* status, unsigned int base_count)
{
    return pow_uint(base_count, status->dimensions);
}

void calculate_direction_combinations(CommonStatus* status, unsigned int base_count, short base[base_count])
{
    //arrays = calloc(arrays_count, sizeof(short*));
    for (unsigned int a = 0; a < status->adjacents_count; a++)
    {
       // arrays[a] = calloc(dimensions, sizeof(short));
        for (unsigned short d = 0; d < status->dimensions; d++)
        {
            status->adjacents[a][d] = base[a / pow_uint(base_count, d) % base_count];
        }
    }
}

void get_adjacents_points(CommonStatus* status, unsigned int coordinates[status->dimensions], unsigned int adjacents[status->adjacents_count][status->dimensions])
{
    for (unsigned int a = 0; a < status->adjacents_count; a++)
    {

        add_relative_vector(status, adjacents[a], coordinates, status->adjacents[a]);
    }
}

unsigned int pow_uint( unsigned int a, unsigned int b)
{
    unsigned int result = 1;

    for (unsigned int i = 0; i < b; i++)
        result *= a;

    return result;
}


void add_relative_vector(CommonStatus* status, unsigned int result[status->dimensions], unsigned int a[status->dimensions], int b[status->dimensions])
{
    for (unsigned short d = 0; d < status->dimensions; d++)
    {
        result[d] = a[d] + b[d];
    }
}

short is_inside(CommonStatus* status, unsigned int coordinates[status->dimensions], unsigned int space_sizes[status->dimensions])
{
    short result = 1;
    for (unsigned short d = 0; d < status->dimensions; d++)
    {
        result &= coordinates[d] >= 0 && coordinates[d] < space_sizes[d] - 1;
    }

    return result;
}
