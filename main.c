#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "damac/game.h"

Game game;
SDL_Surface* screen = NULL;
SDL_Event event;

int main(void) 
{
	int quit = 0;

	if ( ! init_game(&game, screen)) 
	{
		return 1;
	}

	start_game(&game, TwoPlayers);

	while ( ! quit ) 
	{
		if ( ! game.is_running) 
		{
			clean_game(&game);
			return 0;
		}

		while (SDL_PollEvent(&event)) 
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym) 
				{
					case SDLK_UP:
						game.is_running = 0;
						break;
					case SDLK_DOWN: break;
					case SDLK_LEFT: break;
					case SDLK_RIGHT: break;
					default:
						break;
				}
			}
			else if (event.type == SDL_QUIT) 
			{
				quit = 1;
			}

			update_game(&game);
			draw_game(&game);
		}

	}

	clean_game(&game);

	return 0;
}