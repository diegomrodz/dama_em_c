#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "damac/game.h"

Game game;

int main(void) 
{
	start_game(&game, TwoPlayers);

	printf("Hello Wolrd\n");

	return 0;
}