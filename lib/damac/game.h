#ifndef FILE_GAME
#define FILE_GAME

#include "damac/player.h"
#include "damac/board.h"

typedef enum 
{
	TwoPlayers,
	AgainstComputer
} GameOption;

typedef struct 
{
	int round;
	GameOption game_option;
	Board* board;
	Player* black_player;
	Player* white_player;
} Game;

void start_game(Game*, GameOption);

void update_game(Game*);

#endif