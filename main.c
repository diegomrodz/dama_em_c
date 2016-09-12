#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "damac/game.h"
#include "damac/board.h"
#include "damac/player.h"

int comp_char(char that, char with)
{
	return (int)that == (int)with;
}

int main(void) 
{
	Game game;
	Board board;
	Player black, white;
	GameOption option;
	SDL_Surface* screen = NULL;
	SDL_Event event;
	int quit = 0;
	int has_choose = 0;
	char choice;

	while ( ! has_choose)
	{
		printf("Você gostaria de jogar contra a máquina? [Y/N]\n");
		scanf(" %c", &choice);

		if (comp_char(choice, 'Y') || comp_char(choice, 'y'))
		{
			option = AgainstComputer;
			has_choose = 1;
		}
		else if (comp_char(choice, 'N') || comp_char(choice, 'n'))
		{
			option = TwoPlayers;
			has_choose = 1;
		}
	}

	if ( ! init_game(&game, screen)) 
	{
		return 1;
	}

	start_game(&game, &board, &black, &white, option);

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
						move_selection_up(&game);
						break;
					case SDLK_DOWN: 
						move_selection_down(&game);
						break;
					case SDLK_LEFT: 
						move_selection_left(&game);
						break;
					case SDLK_RIGHT: 
						move_selection_right(&game);
						break;
					case SDLK_ESCAPE:
						if (game.input_mode == SelectingPieceMove) 
						{
							escape_selection(&game);
						}
						break;
					case SDLK_RETURN:
						if (game.input_mode == SelectingPiece) 
						{
							player_select_piece(&game);
						}
						else if (game.input_mode == SelectingPieceMove) 
						{
							player_select_place(&game);
						}
						break;
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