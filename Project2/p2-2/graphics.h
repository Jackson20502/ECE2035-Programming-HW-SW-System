#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "globals.h"
 

// The bottom of the screen => y=127
// A macro to reverse the coordinate for convenience (optional).
#define REVERSE_Y(x) (SIZE_Y-(x))

/**
 * Draws a sprite
 */
void draw_sprite1();
void draw_lower_status();
void draw_fireworks();
void draw_thumbs_up();
void draw_crying_face();
void draw_wordle();
void draw_leaderboard();
void draw_arrow1();

#endif // GRAPHICS_H
