#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "damac/graphics.h"


SDL_Surface* load_image(char* filename) 
{
    SDL_Surface* loaded_image = NULL;
    SDL_Surface* optimized_image = NULL;
    
    loaded_image = IMG_Load(filename);
    
    if(loaded_image != NULL)
    {
        optimized_image = SDL_DisplayFormat(loaded_image);
        
        SDL_FreeSurface(loaded_image);

        if( optimized_image != NULL)
        {
            SDL_SetColorKey(optimized_image, SDL_SRCCOLORKEY, SDL_MapRGB(optimized_image->format, 0, 0xFF, 0xFF));
        }
    }
    
    return optimized_image;
}


void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* dest, SDL_Rect* clip)
{
    SDL_Rect offset;
    
    offset.x = x;
    offset.y = y;
    
    SDL_BlitSurface(source, clip, dest, &offset);
}