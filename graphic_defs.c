#include "graphic_defs.h"

double inc = 0.25/360.0 * 2 * 3.1416;
double rot_y = 0;
double rot_x = 0;

int viewport_height = 0;
int viewport_width = 0;
double far_plane = 10.0;
double near_plane = 1;

double right_plane = 2.0;
double left_plane = -2.0;

double up_plane = 1.0;
double bottom_plane = -1.0;

double* z_buffer;
char* framebuffer;

void rotate_X(TRIANGLE* triangle)
{
	double tmp = cos(rot_x)*triangle->v[0].Y - sin(rot_x)*triangle->v[0].Z;
	triangle->v[0].Z = sin(rot_x)*triangle->v[0].Y + cos(rot_x)*triangle->v[0].Z;
	triangle->v[0].Y = tmp;

	tmp = cos(rot_x)*triangle->v[1].Y - sin(rot_x)*triangle->v[1].Z;
	triangle->v[1].Z = sin(rot_x)*triangle->v[1].Y + cos(rot_x)*triangle->v[1].Z;
	triangle->v[1].Y = tmp;

	tmp = cos(rot_x)*triangle->v[2].Y - sin(rot_x)*triangle->v[2].Z;
	triangle->v[2].Z = sin(rot_x)*triangle->v[2].Y + cos(rot_x)*triangle->v[2].Z;
	triangle->v[2].Y = tmp;
	
}

void rotate_Y(TRIANGLE* triangle)
{
	double tmp = cos(rot_y)*triangle->v[0].X + sin(rot_y)*triangle->v[0].Z;
	triangle->v[0].Z = -sin(rot_y)*triangle->v[0].X + cos(rot_y)*triangle->v[0].Z;
	triangle->v[0].X = tmp;

	tmp = cos(rot_y)*triangle->v[1].X + sin(rot_y)*triangle->v[1].Z;
	triangle->v[1].Z = -sin(rot_y)*triangle->v[1].X + cos(rot_y)*triangle->v[1].Z;
	triangle->v[1].X = tmp;

	tmp = cos(rot_y)*triangle->v[2].X + sin(rot_y)*triangle->v[2].Z;
	triangle->v[2].Z = -sin(rot_y)*triangle->v[2].X + cos(rot_y)*triangle->v[2].Z;
	triangle->v[2].X = tmp;
}

void model_view(MODEL* triangle, VIEW_MATRIX* viewing_transform)
{
	// First apply rotation.
	// Rotate about the Y axis.
	
	// Lastly, translation.
}

VECTOR projection_transform(VECTOR* vector)
{
	VECTOR projected;
	projected.X = -near_plane*vector->X/right_plane;
	projected.Y = -near_plane*vector->Y/up_plane;

	projected.W = -vector->Z;

	projected.Z = (far_plane + near_plane)/(far_plane-near_plane);
	projected.Z += (-2*far_plane*near_plane)/((far_plane - near_plane)*projected.W);

	projected.X = projected.X/projected.W;
	projected.Y = projected.Y/projected.W;

	return projected;
}

int edge_function(VECTOR v0, VECTOR v1, VECTOR p)
{
	return ((p.X - v0.X)*(v1.Y - v0.Y) - (p.Y - v0.Y)*(v1.X - v0.X)) > 0;
}

void raster_triangle(TRIANGLE* triangle)
{
	VECTOR vertices[3];

	for(int curr = 0; curr < 3; curr++)
	{
		vertices[curr] = projection_transform(&triangle->v[curr]);
		vertices[curr].X = (vertices[curr].X + 1)*viewport_width/2;
		vertices[curr].Y = (vertices[curr].Y + 1)*viewport_height/2;
	}

	double max_y; // Get maximum and minimum X and Y coords (triangle bounding box).
	double min_y;

	double max_x;
	double min_x;

	//correct winding order.
	double cross_z = (vertices[1].X - vertices[0].X)*(vertices[2].Y - vertices[0].Y) - (vertices[2].X - vertices[0].X)*(vertices[1].Y - vertices[0].Y);
	// cross_z is also the signed area of the parallelogram defined by the two vectors. (v1-v0; v2-v0)

	if(cross_z > 0) // clockwise
	{
		VECTOR v = vertices[1];
		vertices[1] = vertices[2];
		vertices[2] = v;
		cross_z *= -1;
	}

	if(vertices[0].Y <= vertices[1].Y)
	{
		max_y = vertices[1].Y;
		min_y = vertices[0].Y;
	}

	else
	{
		max_y = vertices[0].Y;
		min_y = vertices[1].Y;
	}

	if(max_y <= vertices[2].Y)
		max_y = vertices[2].Y;
	if(min_y >= vertices[2].Y)
		min_y = vertices[2].Y;


	if(vertices[0].X <= vertices[1].X)
	{
		max_x = vertices[1].X;
		min_x = vertices[0].X;
	}

	else
	{
		max_x = vertices[0].X;
		min_x = vertices[1].X;
	}

	if(max_x <= vertices[2].X)
		max_x = vertices[2].X;
	if(min_x >= vertices[2].X)
		min_x = vertices[2].X;

	for(int y_index = (int)min_y; y_index < max_y; y_index++)
	{
		for(int x_index = (int) min_x; x_index < max_x; x_index++)
		{
			VECTOR p = {x_index, y_index, 0, 0};
			// barycentric coordinates associated with V0, V1 and V2 respectively.
			double alpha, beta, gamma;
			alpha = edge_function(vertices[0], vertices[1], p);
			beta = edge_function(vertices[2], vertices[0], p);
			gamma = edge_function(vertices[1], vertices[2], p);

			if(alpha && beta && gamma)
			{
				// Implement z-buffering ()
				//compute barycentric coords by dividing by the signed area
				alpha /= cross_z; 
				beta /= cross_z;
				gamma /= cross_z;

				//now interpolate z' (projected.Z) which is a function of 1/z, which can be linearly interpolated using screen-space coords.
				double interpolated = 1/(alpha*vertices[2].Z + beta*vertices[1].Z + gamma*vertices[0].Z);
				if(z_buffer[y_index*viewport_width + x_index] > interpolated)
				{
					framebuffer[y_index*viewport_width + x_index] = triangle->COLOUR;
					z_buffer[y_index*viewport_width + x_index] = interpolated;
				}
				//putchar(triangle->COLOUR);
			}
		}
	}
}
