#ifndef PLAYER_H
#define PLAYER_H

#include "graphics_defs.h"

typedef struct player_t
{
    VECTOR position; // W component not used, might be considered a waste of space but I doesn't really matter here.
    VECTOR look_at_dir; // Same as above. That's 16 bytes gone to waste!
    
    int total_ammo;
    int total_health;
};














#endif