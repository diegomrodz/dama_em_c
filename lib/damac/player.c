#include "damac/piece.h"
#include "damac/player.h"
#include "damac/board.h"

void new_player(Player* player, PieceColor color) 
{
	player->score = 0;
	player->color = color;
	player->x = color == Black ? 1 : DAMAC_BOARD_SIZE - 1;
	player->y = color == Black ? 0 : DAMAC_BOARD_SIZE - 1;
}