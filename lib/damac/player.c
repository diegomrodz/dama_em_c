#include "damac/piece.h"
#include "damac/player.h"

void new_player(Player* player, PieceColor color) 
{
	player->score = 0;
	player->color = color;
}