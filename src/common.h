#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <linux/limits.h>

typedef struct SCluster
{
	unsigned int id;

	unsigned long  center; // encoded position
	unsigned int   radius;

	unsigned int   creation_time;
    unsigned int   volume;

    unsigned short growing;
} Cluster;

typedef enum SColorType
{
    RANDOM_ACID, GRADIENT_VOLUME, GRADIENT_RADIUS, GRADIENT_AGE, GRADIENT_BIRTH
} ColorType;

typedef enum SRenderType
{
    R_2D, R_3D
} RenderType;


typedef struct SRender
{
	char name[256];
    char output_directory[PATH_MAX];

    RenderType type;

    unsigned short axis_1;
    unsigned short axis_2;
    unsigned short axis_3;

	unsigned int*   cut_levels;
	unsigned short* cut_directions;
	ColorType color_scheme;
	
	
	unsigned int  colors_size;
	unsigned int* colors;
} Render;


typedef struct SCommonStatus
{
    unsigned short dimensions;

    unsigned long* cartesian_moltiplicators; // should be []
    unsigned int** polar_moltiplicators;    // should be [][]
    double* min_polar_angles; // should be []

    unsigned int  max_radius;
    unsigned int  space_volume;
    unsigned int* space_sizes;

    unsigned int adjacents_count;
    int** adjacents;

    unsigned int*  stat_pixel_grow; // contains the amount of pixel grow at every time event
    unsigned long  stat_pixel_grow_total; // contains the amount of pixel grow at every time event
} CommonStatus;


CommonStatus* init_common(unsigned short dimensions, unsigned int space_sizes[dimensions], unsigned int duration);
void free_common(CommonStatus* status);


unsigned long encode_position_cartesian(CommonStatus* status, unsigned int coordinates[status->dimensions]);
void decode_position_cartesian(CommonStatus* status, unsigned int coordinates[status->dimensions], unsigned long encoded_position);
unsigned long encode_position_polar(CommonStatus* status, double angles[status->dimensions-1], unsigned int radius);
void decode_position_polar(CommonStatus* status, double angles[status->dimensions-1], unsigned int radius, unsigned long encoded_position);

double min_polar_angle(unsigned int radius);

void dimension_to_label(char dest[8], CommonStatus* status, unsigned short d);
unsigned short label_to_dimension(CommonStatus* status, char* label);

void get_adjacents_points(CommonStatus* status, unsigned int coordinates[status->dimensions], unsigned int adjacents[status->adjacents_count][status->dimensions]);
unsigned int calculate_direction_combinations_count(CommonStatus* status, unsigned int base_count);

void calculate_direction_combinations(CommonStatus* status, unsigned int base_count, short base[base_count]);
unsigned int calculate_distance(CommonStatus* status, unsigned int point1[status->dimensions], unsigned int point2[status->dimensions]);

unsigned int pow_uint( unsigned int a, unsigned int b);

void convert_cartesian_to_polar_angles(CommonStatus* status,  double angles[status->dimensions-1], unsigned int coordinates[status->dimensions]);
void convert_polar_angles_to_cartesian(CommonStatus* status, double angles[status->dimensions-1], unsigned int radius, int coordinates[status->dimensions]);

void add_relative_vector(CommonStatus* status, unsigned int result[status->dimensions], unsigned int a[status->dimensions], int b[status->dimensions]);
short is_inside(CommonStatus* status, unsigned int coordinates[status->dimensions], unsigned int space_sizes[status->dimensions]);

unsigned int get_surface_points_count(CommonStatus* status, unsigned int radius);



#define 	M_E   2.7182818284590452354
#define 	M_LOG2E   1.4426950408889634074 /* log_2 e */
#define 	M_LOG10E   0.43429448190325182765 /* log_10 e */
#define 	M_LN2   0.69314718055994530942 /* log_e 2 */
#define 	M_LN10   2.30258509299404568402 /* log_e 10 */
#define 	M_PI   3.14159265358979323846 /* pi */
#define 	M_PI_2   1.57079632679489661923 /* pi/2 */
#define 	M_PI_4   0.78539816339744830962 /* pi/4 */
#define 	M_1_PI   0.31830988618379067154 /* 1/pi */
#define 	M_2_PI   0.63661977236758134308 /* 2/pi */
#define 	M_2_SQRTPI   1.12837916709551257390 /* 2/sqrt(pi) */
#define 	M_SQRT2   1.41421356237309504880 /* sqrt(2) */
#define 	M_SQRT1_2   0.70710678118654752440 /* 1/sqrt(2) */


#endif // COMMON_H_INCLUDED
