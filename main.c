#include <stdio.h>
#include "SDL/SDL.h"

int main(void) 
{
	SDL_Init( SDL_INIT_EVERYTHING );

	printf("Hello Wolrd\n");

	SDL_Quit();

	return 0;
}