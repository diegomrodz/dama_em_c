#include "damac/game.h" 
#include "damac/piece.h"
#include "damac/player.h"
#include "damac/board.h"

void start_game (Game* game, GameOption option) 
{
	Board board;
	Player black, white;

	init_board(&board);
	stater_board(&board);

	game->board = &board;

	new_player(&white, White);
	new_player(&black, Black);

	game->white_player = &white;
	game->black_player = &black;
}

void update_game (Game* game) 
{

}