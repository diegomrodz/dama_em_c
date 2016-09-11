#ifndef FILE_BOARD
#define FILE_BOARD

#include "damac/piece.h"

#define DAMAC_BOARD_SIZE 8
#define DAMAC_PIECES_QTD 12

/**
 * Estrutura responsável por carregar informações do tabuleiro.
 */
typedef struct 
{
	// Número de peças restantes no tabuleiro
	int pieces_left;
	// Lista de peças no tabuleiro
	Piece pieces[DAMAC_PIECES_QTD * DAMAC_PIECES_QTD];
} Board;

/**
 * Estrtura auxiliar para indicar uma posição no tabuleiro
 */
typedef struct 
{
	int x, y;
} Place;

/**
 * Inicializa o tabuleiro passado como argumento
 */
void init_board(Board*);

/**
 * Insere as peças em suas posições iniciais
 */
void stater_board(Board*);

/**
 * Faz uma cópia do tabuleiro para outro tabuleiro
 */
void copy_board(Board* source, Board* dest);

/**
 * Adiciona uma peça ao tabuleiro
 */
void add_piece(Board*, Piece);

/**
 * Retorna a peça na posição x,y do tabuleiro
 */
Piece* get_piece(Board*, int xPos, int yPos);

/**
 * Remove a peça do tabuleiro na posição indicada
 */
int remove_piece(Board*, int xPos, int yPos);

/**
 * Valida a posição de x,y para um tabuleiro 8x8
 */
int is_valid_location(int xPos, int yPos);

/**
 * Retorna se a peça pode se mover à posição x,y no tabuleiro
 */
int can_move_piece(Board*, Piece*, int xPos, int yPos); 

/**
 * Retorna se a peça pode comer a outra no tabuleiro
 */
int can_eat_piece(Board*, Piece* eater, Piece* eaten);

/**
 * Come a outra peça no tabuleiro
 */
int eat_piece(Board*, Piece* eater, Piece* eaten);

/**
 * Conta o número de peças da cor indicada no tabuleiro
 */
int count_pieces(Board*, PieceColor);

/**
 * Popula um array com as peças comiveis de uma peça no tabuleiro
 */
void eatable_pieces(Piece**, Board*, Piece*);

/**
 * Retorna um número indicando se houve um vencedor no tabuleiro
 */
int has_winner (Board*);

#endif