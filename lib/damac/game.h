#ifndef FILE_GAME
#define FILE_GAME

#include "damac/player.h"
#include "damac/board.h"
#include "damac/piece.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

typedef enum 
{
	TwoPlayers,
	AgainstComputer
} GameOption;

typedef enum 
{
	SelectingPiece,
	SelectingPieceMove
} InputMode;

typedef struct 
{
	int round;
	int is_running;
	int place_selected_index;
	int place_selected_length;
	GameOption game_option;
	InputMode input_mode;
	Place movable_places[4];
	Piece* selected_piece;
	SDL_Surface* screen;
	Board* board;
	Player* black_player;
	Player* white_player;
} Game;

SDL_Surface* DAMAC_WOOD_SPREADSHEET;
SDL_Surface* DAMAC_STONES_SPREADSHEET;
SDL_Surface* DAMAC_SELECTION_SPREADSHEET;

SDL_Rect DAMAC_WOOD_WHITE_VERTICAL;
SDL_Rect DAMAC_WOOD_WHITE_HORIZONTAL;

SDL_Rect DAMAC_WOOD_BLACK_VERTICAL;
SDL_Rect DAMAC_WOOD_BLACK_HORIZONTAL;

SDL_Rect DAMAC_WOOD_BOARD_UP_LEFT;
SDL_Rect DAMAC_WOOD_BOARD_UP_CENTER;
SDL_Rect DAMAC_WOOD_BOARD_UP_RIGHT;

SDL_Rect DAMAC_WOOD_BOARD_CENTER_LEFT;
SDL_Rect DAMAC_WOOD_BOARD_CENTER_RIGHT;

SDL_Rect DAMAC_WOOD_BOARD_DOWN_LEFT;
SDL_Rect DAMAC_WOOD_BOARD_DOWN_CENTER;
SDL_Rect DAMAC_WOOD_BOARD_DOWN_RIGHT;

SDL_Rect DAMAC_STONES_BLACK;
SDL_Rect DAMAC_STONES_WHITE;

SDL_Rect DAMAC_STONES_BLACK_QUEEN;
SDL_Rect DAMAC_STONES_WHITE_QUEEN;

SDL_Rect DAMAC_SELECTION_BLUE;
SDL_Rect DAMAC_SELECTION_RED;

void start_game (Game*, Board*, Player* black, Player* white, GameOption); 

void apply_tile(Game*, int xPos, int yPos, SDL_Rect*); 

void apply_piece(Game*, int xPos, int yPos, SDL_Rect*);

void apply_selection(Game*, int xPos, int yPos, SDL_Rect*);

void player_select_piece(Game*);

void set_selectable_places(Game*);

void escape_selection(Game*);

void player_select_place(Game*);

void update_game(Game*);

void draw_game (Game*);

int init_game(Game*, SDL_Surface* screen);

void move_selection_up(Game*);

void move_selection_down(Game*);

void move_selection_left(Game*);

void move_selection_right(Game*);

void clean_game(Game*); 

#endif