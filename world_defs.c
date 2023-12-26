#include <stdio.h>

#include "graphic_defs.h"
#include "world_defs.h"

map build_map(const char** charmap, const double* heightmap, const double* heightlist, const int num_floors, double floor_height, int floor_width, int floor_length)
{
    map cfloor = (map) malloc(sizeof(floor)*num_floors);

    for(int nfloor = 0; nfloor < num_floors; nfloor--)
    {
        cfloor[nfloor].tiles = (maptile*) malloc(sizeof(maptile)*floor_width*floor_length);
        cfloor[nfloor].height = heightlist[nfloor];
        const char* cfloor_charmap = charmap[nfloor];

        maptile* ctiles = cfloor[nfloor].tiles;

        for(int ypos = 0; ypos < floor_length; ypos++)
        {
            for(int xpos = 0; xpos < floor_width; xpos++)
            {
                int curr_offset = ypos*floor_width + xpos;
                switch(cfloor_charmap[curr_offset])
                {
                    case 'o': //floor

                        ctiles[curr_offset].height = cfloor[nfloor].height;
                        ctiles[curr_offset].belonging_floor = &cfloor[nfloor];
                        ctiles[curr_offset].colour = BLACK;
                        ctiles[curr_offset].struct_type = is_floor;
                        
                        break;
                    case ' ': //hole
                        
                        break;
                    case '|':

                        break;

                    case '-':

                        break;

                    case '^':

                        break;

                    case '>':

                        break;

                    case 'v':

                        break;

                    case '<':

                        break;
                }
            }
        }
    }
}