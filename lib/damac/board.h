#ifndef FILE_BOARD
#define FILE_BOARD

#include "damac/piece.h"

#define DAMAC_BOARD_SIZE 8
#define DAMAC_PIECES_QTD 12

typedef struct 
{
	int pieces_left;
	Piece pieces[DAMAC_PIECES_QTD * DAMAC_PIECES_QTD];
} Board;

void init_board(Board*);

void stater_board(Board*);

void copy_board(Board* source, Board* dest);

void add_piece(Board*, Piece);

Piece* get_piece(Board*, int xPos, int yPos);

int remove_piece(Board*, int xPos, int yPos);

int is_valid_location(int xPos, int yPos);

int can_move_piece(Board*, Piece*, int xPos, int yPos); 

int can_eat_piece(Board*, Piece* eater, Piece* eaten);

int eat_piece(Board*, Piece* eater, Piece* eaten);

int count_pieces(Board*, PieceColor);

void eatable_pieces(Piece**, Board*, Piece*);

int has_winner (Board*);

#endif