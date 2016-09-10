#include <stdio.h>
#include <stdlib.h>
#include "damac/board.h"
#include "damac/piece.h"

void init_board(Board* board) 
{
	board->pieces_left = 0;
}

void stater_board(Board* board) 
{
	int x, y;

	for (y = 1; y <= 3; y += 1) 
	{
		x = y % 2 == 0 ? 0 : 1; 

		for (; x < DAMAC_BOARD_SIZE; x += 2) 
		{
			board->pieces_left += 1;

			board->pieces[board->pieces_left - 1].color = Black;
			board->pieces[board->pieces_left - 1].x = x;
			board->pieces[board->pieces_left - 1].y = y - 1;
			board->pieces[board->pieces_left - 1].is_queen = 0;
		}

		x = y % 2 == 0 ? 1 : 0;

		for (; x < DAMAC_BOARD_SIZE; x += 2) 
		{
			board->pieces_left += 1;

			board->pieces[board->pieces_left - 1].color = White;
			board->pieces[board->pieces_left - 1].x = x;
			board->pieces[board->pieces_left - 1].y = DAMAC_BOARD_SIZE - y;
			board->pieces[board->pieces_left - 1].is_queen = 0;
		}
	}
}

void copy_board(Board* source, Board* dest) 
{
	int i;

	for (i = 0; i < source->pieces_left; i += 1) 
	{
		add_piece(dest, source->pieces[i]);
	}
}

void add_piece(Board* board, Piece piece) 
{
	board->pieces_left += 1;
	board->pieces[board->pieces_left - 1] = piece;
}

Piece* get_piece(Board* board, int x, int y) 
{
	int i;

	if ( ! is_valid_location(x, y)) 
	{
		return NULL;
	}

	for (i = 0; i < board->pieces_left; i += 1) 
	{
		if (board->pieces[i].x == x && board->pieces[i].y == y) 
		{
			return &board->pieces[i];
		}
	}

	return NULL;
}

int is_valid_location(int x, int y) 
{
	if (x < 0 || y < 0 || x > DAMAC_BOARD_SIZE - 1 || y > DAMAC_BOARD_SIZE - 1) 
	{
		return 0;
	}

	if (y % 2 == 0 && x % 2 == 0) 
	{
		return 0;
	}

	return 1;
}

int can_move_piece(Board* board, Piece* piece, int x, int y) 
{
	if ( ! is_valid_location(x, y)) 
	{
		return 0;
	}

	Piece* aux = get_piece(board, x, y);

	if (aux != NULL && aux->color == piece->color && ! can_eat_piece(board, piece, aux)) 
	{
		return 0;
	}

	return 1;
}

int can_eat_piece(Board* board, Piece* eater, Piece* eaten) 
{
	if (eater->color == eaten->color) 
	{
		return 0;
	}

	if ( ! eater->is_queen) 
	{
		if (eater->color == White) 
		{
			if (eater->y < eaten->y) 
			{
				return 0;
			}

			if (eater->x < eaten->x) 
			{
				return can_move_piece(board, eater, eaten->x + 1, eaten->y - 1); 
			}
			else 
			{
				return can_move_piece(board, eater, eaten->x - 1, eaten->y - 1); 
			}
		}
		else 
		{
			if (eater->y > eaten->y) 
			{
				return 0;
			} 

			if (eater->x < eaten->x) 
			{
				return can_move_piece(board, eater, eaten->x + 1, eaten->y + 1); 
			}
			else 
			{
				return can_move_piece(board, eater, eaten->x - 1, eaten->y + 1); 
			}
		}
	}
	else 
	{
		if (eater->y < eaten->y) 
		{
			if (eater->x < eaten->x) 
			{
				return can_move_piece(board, eater, eaten->x + 1, eaten->y - 1); 
			}
			else 
			{
				return can_move_piece(board, eater, eaten->x - 1, eaten->y - 1); 
			}
		}
		else
		{
			if (eater->x < eaten->x) 
			{
				return can_move_piece(board, eater, eaten->x + 1, eaten->y + 1); 
			}
			else 
			{
				return can_move_piece(board, eater, eaten->x - 1, eaten->y + 1); 
			}
		}
	}
}

void eatable_pieces(Piece** eatables, Board* board, Piece* piece) 
{
	int count = 0;
	Piece* neighbor;

	neighbor = get_piece(board, piece->x + 1, piece->y + 1); 

	if (neighbor != NULL && can_eat_piece(board, piece, neighbor)) 
	{
		eatables[count++] = neighbor;
	}

	neighbor = get_piece(board, piece->x - 1, piece->y - 1); 

	if (neighbor != NULL && can_eat_piece(board, piece, neighbor)) 
	{
		eatables[count++] = neighbor;
	}

	neighbor = get_piece(board, piece->x - 1, piece->y + 1); 

	if (neighbor != NULL && can_eat_piece(board, piece, neighbor)) 
	{
		eatables[count++] = neighbor;
	}

	neighbor = get_piece(board, piece->x + 1, piece->y - 1); 

	if (neighbor != NULL && can_eat_piece(board, piece, neighbor)) 
	{
		eatables[count++] = neighbor;
	}
}

int eat_piece(Board* board, Piece* eater, Piece* eaten) 
{
	if ( ! eater->is_queen) 
	{
		if (eater->color == White) 
		{
			if (eater->x < eaten->x) 
			{
				move_piece(eater, eater->x + 2, eater->y - 2);
			}
			else 
			{
				move_piece(eater, eater->x - 2, eater->y - 2);
			}
		}
		else 
		{
			if (eater->x < eaten->x) 
			{
				move_piece(eater, eater->x + 2, eater->y + 2);
			}
			else 
			{
				move_piece(eater, eater->x - 2, eater->y + 2);
			}
		}
	}
	else 
	{
		if (eater->y < eaten->y) 
		{
			if (eater->x < eaten->x) 
			{
				move_piece(eater, eater->x + 2, eater->y - 2); 
			}
			else 
			{
				move_piece(eater, eater->x - 2, eater->y - 2); 
			}
		}
		else 
		{
			if (eater->x < eaten->x) 
			{
				move_piece(eater, eater->x + 2, eater->y + 2); 
			}
			else 
			{
				move_piece(eater, eater->x - 2, eater->y + 2); 
			}			
		}
	}

	remove_piece(board, eaten->x, eaten->y);
}

int remove_piece(Board* board, int x, int y) 
{
	int i, j;

	for (i = 0; i < board->pieces_left; i += 1) 
	{
		if (board->pieces[i].x == x && board->pieces[i].y == y) 
		{
			for (j = i; j < board->pieces_left; j += 1) 
			{
				board->pieces[j] = board->pieces[j + 1];
			}

			board->pieces_left -= 1;

			return 1;
		}
	}

	return -1;
}

int count_pieces(Board* board, PieceColor color) 
{
	int i, count = 0;

	for (i = 0; i < board->pieces_left; i += 1) 
	{
		if (board->pieces[i].color == color) 
		{
			count += 1;
		}
	}

	return count;
}

int has_winner (Board* board) 
{
	int i;
	int black_has_won = 1, white_has_won = 1;

	if (board->pieces_left == 0) 
	{
		return -1;
	}

	for (i = 0; i < board->pieces_left; i += 1) 
	{
		if (board->pieces[i].color == White) 
		{
			black_has_won = 0;
		}
		else 
		{
			white_has_won = 0;
		}

		if ( ! black_has_won && ! white_has_won) 
		{
			return -1;
		}
	}

	if (black_has_won) 
	{
		return 0;
	}
	
	if (white_has_won)
	{
		return 1;
	}

	return -1;
}