#ifndef WORLDDEFS_H
#define WORLDDEFS_H

#include "graphic_defs.h"

typedef struct
{
    
    enum struct_type
    {
        is_wall,
        is_floor, 
        is_ramp
    } struct_type;

    double height; // This value not only applies for walls, but also for floors.
    floor* floor; // pointer to the floor this tile belongs to.
    VECTOR vertices[4];

    char colour; // "texture" lol

} maptile;

typedef struct 
{
    maptile* tiles;
    double height;

} floor;

typedef floor* map;

/*
    The heightmap is a bidimensional map where each unit is the height of the corresponding tile in the charmap.
    The heightlist is an array of the corresponding height of each floor.

    The height of a tile is thus computed tile.height = heightmap[floor_width*y + x] + heightlist[nfloor];
    Where nfloor = number of the floor in question.
*/

map build_map(const char** charmap, const double* heightmap, const double* heightlist, const int num_floors, double floor_height, int floor_width, int floor_length); // Constructs a map (array of floors) from a charmap and returns it.

#endif