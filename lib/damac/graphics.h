#ifndef FILE_GRAPHICS
#define FILE_GRAPHICS

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#define DAMAC_SCREEN_WIDTH 800
#define DAMAC_SCREEN_HEIGHT 600
#define DAMAC_SCREEN_BPP 32

SDL_Surface* load_image(char* filename);

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* dest, SDL_Rect* clip);

#endif