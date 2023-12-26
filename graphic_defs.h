#ifndef _GRAPHIC_DEFS_H
#define _GRAPHIC_DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#ifdef _WIN32

#include <Windows.h>

#else

#include <sys/ioctl.h>
#include <unistd.h>

#endif

#define YELLOW ';'
#define BLUE 'b'
#define RED 'm'
#define GREEN 'o'
#define CYAN 'n'
#define BLACK '/'

typedef struct MODEL_MATRIX_DESCR//This structure describes the model matrix for a certain... model.
{
	bool rot_flag;
	
	double angle_x;
	double angle_y;
	double angle_z;
	
	double translation_x;
	double translation_y;
	double translation_z;
	
} MODEL_MATRIX;

typedef struct VIEWING_TRANSFORM_MATRIX
{
	
	
} VIEW_MATRIX;

typedef struct
{
	TRIANGLE* triangles; // triangles that form a model.

} MODEL;

typedef struct
{
	double X;
	double Y;
	double Z;
	double W;
} VECTOR;

typedef struct
{
	VECTOR v[3];
	char COLOUR; // "COLOUR" is a character, in this case. 	
} TRIANGLE;

extern int viewport_height;
extern int viewport_width;
extern double far_plane;
extern double near_plane;

extern double right_plane;
extern double left_plane;

extern double up_plane;
extern double bottom_plane;

extern double* z_buffer;
extern char* framebuffer;

VECTOR base_tiles[3][4] = {{{0.0, 0.0, 1.0, 1.0}, {1.0, 0.0, 1.0, 1.0}, {1.0, 0.0, 0.0, 1.0}, {0.0, 0.0, 0.0, 1.0}}, //floor
 						   {{0.0, 1.0, 0.0, 1.0}, {0.0, 1.0, 1.0, 1.0}, {0.0, 0.0, 1.0, 1.0}, {0.0, 0.0, 0.0, 1.0}}, // "vertical" wall
 					 	   {{0.0, 1.0, 0.0, 1.0}, {1.0, 1.0, 0.0, 1.0}, {1.0, 0.0, 0.0, 1.0}, {0.0, 0.0, 0.0, 1.0}}};// "horizontal" wall


#ifdef _WIN32

extern HANDLE console_output;

#else

extern FILE* console_output;

#endif

void rotate_X(TRIANGLE*);
void rotate_Y(TRIANGLE*);
void model_view(MODEL*);
VECTOR projection_transform(VECTOR*);
int edge_function(VECTOR, VECTOR, VECTOR);
void raster_triangle(TRIANGLE* triangle);

#endif
