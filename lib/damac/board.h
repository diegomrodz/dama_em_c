#ifndef FILE_BOARD
#define FILE_BOARD

#include "damac/piece.h"

#define BOARD_SIZE 8
#define PIECES_QTD 12

typedef struct 
{
	int pieces_left;
	Piece** pieces;
} Board;

void init_board(Board*);

void stater_board(Board*);

void add_piece(Board*, Piece*);

Piece* get_piece(Board*, int xPos, int yPos);

int remove_piece(Board*, int xPos, int yPos);

int is_valid_location(int xPos, int yPos);

int can_move_piece(Board*, Piece*, int xPos, int yPos); 

int can_eat_piece(Board* board, Piece* eater, Piece* eaten);

#endif