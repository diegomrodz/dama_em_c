#ifndef FILE_PIECE
#define FILE_PIECE

typedef enum 
{
	Black = 0,
	White = 1
} PieceColor;

typedef struct 
{
	int x, y;
	int is_queen;
	PieceColor color;
} Piece;

void init_piece(Piece*, PieceColor, int xPos, int yPos);

void move_piece(Piece*, int xPos, int yPos);

#endif