#include "damac/piece.h"

void init_piece(Piece* p, PieceColor pc, int x, int y) 
{
	p->color = pc;
	p->is_queen = 0;
	p->x = x;
	p->y = y;
}