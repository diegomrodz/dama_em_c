#ifndef FILE_PLAYER
#define FILE_PLAYER

#include "damac/piece.h"

typedef struct
{
	int score;
	PieceColor color;
} Player;

void new_player(Player*, PieceColor);

#endif