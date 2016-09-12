
#include "damac/node.h"
#include "damac/piece.h"

int simple_score(Node* node, PieceColor color) 
{
	Piece piece;
	int score = 0;
	int i;

	for (i = 0; i < node->state->pieces_left; i += 1) 
	{
		piece = node->state->pieces[i];

		if (piece.color == color) 
		{
			if (is_on_conner(&piece)) 
			{
				score += 1;
			}

			if (piece.is_queen) 
			{
				score += 2;
			}
			else
			{
				score += 1;
			}
		}
		else 
		{
			if (is_on_conner(&piece)) 
			{
				score -= 1;
			}

			if (piece.is_queen) 
			{
				score -= 2;
			}
			else
			{
				score -= 1;
			}	
		}
	}

	return score;
}