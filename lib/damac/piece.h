#ifndef FILE_PIECE
#define FILE_PIECE

typedef enum 
{
	Black,
	White
} PieceColor;

typedef struct 
{
	int x, y;
	int is_queen;
	PieceColor color;
} Piece;

void init_piece(Piece*, PieceColor, int xPos, int yPos);
void move_piece(Piece* piece, int xPos, int yPos);

#endif