#include "damac/piece.h"
#include "damac/board.h"

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

	if (piece->color == White) 
	{
		if (piece->y == 0) 
		{
			piece->is_queen = 1;
		}
	}
	else 
	{
		if (piece->y == DAMAC_BOARD_SIZE - 1) 
		{
			piece->is_queen = 1;
		}
	}
}


int is_on_conner(Piece* piece) 
{
	return piece->x == 0 || piece->x == DAMAC_BOARD_SIZE - 1 || piece->y == 0 || piece->y == DAMAC_BOARD_SIZE - 1;
}