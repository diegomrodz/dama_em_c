#include "damac/piece.h"

void init_piece(Piece* piece, PieceColor pc, int x, int y) 
{
	piece->color = pc;
	piece->is_queen = 0;
	piece->x = x;
	piece->y = y;
}

void move_piece(Piece* piece, int x, int y) 
{
	piece->x = x;
	piece->y = y;
}