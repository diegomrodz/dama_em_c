#include "damac/game.h" 
#include "damac/piece.h"
#include "damac/player.h"
#include "damac/board.h"
#include "damac/graphics.h"

void start_game (Game* game, Board* board, Player* black, Player* white, GameOption option) 
{
	init_board(board);
	stater_board(board);

	game->board = board;

	new_player(white, White);
	new_player(black, Black);

	game->white_player = white;
	game->black_player = black;

	game->is_running = 1;
	game->round = 0;
	game->input_mode = SelectingPiece;
}

void update_game (Game* game) 
{
	int winner = has_winner(game->board);

	if (winner != -1) 
	{
		if (winner == 0) 
		{
			printf("O Jogador preto venceu!\n");
		}
		else 
		{
			printf("O Jogador branco venceu!\n");
		}

		game->is_running = 0;
	}
}

void apply_tile(Game* game, int x, int y, SDL_Rect* tile) 
{
	apply_surface(x * 32, y * 32, DAMAC_WOOD_SPREADSHEET, game->screen, tile);
}

void apply_piece(Game* game, int x, int y, SDL_Rect* piece) 
{
	apply_surface(x * 32, y * 32, DAMAC_STONES_SPREADSHEET, game->screen, piece);
}

void apply_selection(Game* game, int x, int y, SDL_Rect* piece) 
{
	apply_surface(x * 32, y * 32, DAMAC_SELECTION_SPREADSHEET, game->screen, piece);
}

void draw_game (Game* game) 
{
	int x, y, i;

	// Clear screen
	SDL_FillRect(game->screen, &game->screen->clip_rect, SDL_MapRGB(game->screen->format, 0x00, 0x00, 0x00));

	for (y = -1; y <= DAMAC_BOARD_SIZE; y += 1) 
	{
		for (x = -1; x <= DAMAC_BOARD_SIZE; x += 1) 
		{
			if (x == -1 || y == -1) 
			{
				if (x == -1 && y == -1) 
				{
					apply_tile(game, 0, 0, &DAMAC_WOOD_BOARD_UP_LEFT);
				}	
				else if (x == -1 && y < DAMAC_BOARD_SIZE) 
				{
					apply_tile(game, 0, y + 1, &DAMAC_WOOD_BOARD_CENTER_LEFT);		
				}
				else if (x < DAMAC_BOARD_SIZE && y == -1) 
				{
					apply_tile(game, x + 1, 0, &DAMAC_WOOD_BOARD_UP_CENTER);
				}
				else if (x == -1 && y == DAMAC_BOARD_SIZE) 
				{
					apply_tile(game, x + 1, y + 1, &DAMAC_WOOD_BOARD_DOWN_LEFT);
				}
				else if (x == DAMAC_BOARD_SIZE && y == -1) 
				{
					apply_tile(game, x + 1, y + 1, &DAMAC_WOOD_BOARD_UP_RIGHT);
				}			
			}
			else if (x == DAMAC_BOARD_SIZE || y == DAMAC_BOARD_SIZE) 
			{
				if (x == DAMAC_BOARD_SIZE && y == DAMAC_BOARD_SIZE) 
				{
					apply_tile(game, x + 1, y + 1, &DAMAC_WOOD_BOARD_DOWN_RIGHT);
				}
				else if (x == DAMAC_BOARD_SIZE && y > -1 && y < DAMAC_BOARD_SIZE) 
				{
					apply_tile(game, x + 1, y + 1, &DAMAC_WOOD_BOARD_CENTER_RIGHT);
				}
				else if (y == DAMAC_BOARD_SIZE && x > -1 && x < DAMAC_BOARD_SIZE) 
				{
					apply_tile(game, x + 1, y + 1, &DAMAC_WOOD_BOARD_DOWN_CENTER);
				}
			}
			else if (x > -1 && x < DAMAC_BOARD_SIZE && y > -1 && y < DAMAC_BOARD_SIZE) 
			{
				if (y % 2 == 0) 
				{
					if (x % 2 == 0) 
					{
						apply_tile(game, x + 1, y + 1, &DAMAC_WOOD_WHITE_VERTICAL);
					}
					else 
					{
						apply_tile(game, x + 1, y + 1, &DAMAC_WOOD_BLACK_VERTICAL);
					}
				}
				else 
				{
					if (x % 2 == 0) 
					{
						apply_tile(game, x + 1, y + 1, &DAMAC_WOOD_BLACK_HORIZONTAL);
					}
					else 
					{
						apply_tile(game, x + 1, y + 1, &DAMAC_WOOD_WHITE_HORIZONTAL);
					}
				}
			}
		}
	}

	for (i = 0; i < game->board->pieces_left; i += 1) 
	{
		if (game->board->pieces[i].color == Black) 
		{
			apply_piece(game, game->board->pieces[i].x + 1, game->board->pieces[i].y + 1, &DAMAC_STONES_BLACK);
		}
		else 
		{
			apply_piece(game, game->board->pieces[i].x + 1, game->board->pieces[i].y + 1, &DAMAC_STONES_WHITE);
		}
	}

	if (game->input_mode == SelectingPiece) 
	{
		if (game->round % 2 == 0) 
		{
			apply_selection(game, game->white_player->x + 1, game->white_player->y + 1, &DAMAC_SELECTION_BLUE);
		}
		else 
		{
			apply_selection(game, game->black_player->x + 1, game->black_player->y + 1, &DAMAC_SELECTION_BLUE);
		}
	}
	else if (game->input_mode == SelectingPieceMove) 
	{
		for (i = 0; i < game->place_selected_length; i += 1) 
		{
			if (i == game->place_selected_index) 
			{
				apply_selection(game, game->movable_places[i].x + 1, game->movable_places[i].y + 1, &DAMAC_SELECTION_RED);
			}
			else 
			{
				apply_selection(game, game->movable_places[i].x + 1, game->movable_places[i].y + 1, &DAMAC_SELECTION_BLUE);
			}
		}
	}

	// Refresh screen
	SDL_Flip(game->screen);
}

int init_game(Game* game, SDL_Surface* screen) 
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) 
	{
		return 1;
	}

	screen = SDL_SetVideoMode(32 * (DAMAC_BOARD_SIZE + 2), 32 * (DAMAC_BOARD_SIZE + 2), DAMAC_SCREEN_BPP, SDL_SWSURFACE);

	if (screen == NULL) 
	{
		return 0;
	}

	SDL_WM_SetCaption("Dama em C", NULL);

	game->screen = screen;

	// Inicializa todas spread sheets
	DAMAC_WOOD_SPREADSHEET = load_image("res/wood.png");
	DAMAC_STONES_SPREADSHEET = load_image("res/stones.png");
	DAMAC_SELECTION_SPREADSHEET = load_image("res/selection.png");

	DAMAC_WOOD_WHITE_VERTICAL = (SDL_Rect){ .x = 0, .y = 0, .w = 33, .h = 33 };
	DAMAC_WOOD_WHITE_HORIZONTAL = (SDL_Rect){ .x = 33, .y = 0, .w = 33, .h = 33 };

	DAMAC_WOOD_BLACK_VERTICAL = (SDL_Rect){ .x = 0, .y = 64, .w = 33, .h = 33 };
	DAMAC_WOOD_BLACK_HORIZONTAL = (SDL_Rect){ .x = 33, .y = 64, .w = 33, .h = 33 };

	DAMAC_WOOD_BOARD_UP_LEFT = (SDL_Rect){ .x = 64, .y = 0, .w = 33, .h = 33 };
	DAMAC_WOOD_BOARD_UP_CENTER = (SDL_Rect){ .x = 96, .y = 0, .w = 33, .h = 33 };
	DAMAC_WOOD_BOARD_UP_RIGHT = (SDL_Rect){ .x = 128, .y = 0, .w = 33, .h = 33 };

	DAMAC_WOOD_BOARD_CENTER_LEFT = (SDL_Rect){ .x = 64, .y = 32, .w = 33, .h = 33 };
	DAMAC_WOOD_BOARD_CENTER_RIGHT = (SDL_Rect){ .x = 128, .y = 32, .w = 33, .h = 33 };

	DAMAC_WOOD_BOARD_DOWN_LEFT = (SDL_Rect){ .x = 64, .y = 64, .w = 33, .h = 33 };
	DAMAC_WOOD_BOARD_DOWN_CENTER = (SDL_Rect){ .x = 96, .y = 64, .w = 33, .h = 33 };
	DAMAC_WOOD_BOARD_DOWN_RIGHT = (SDL_Rect){ .x = 128, .y = 64, .w = 33, .h = 33 };

	DAMAC_STONES_BLACK = (SDL_Rect){ .x = 0, .y = 0, .w = 32, .h = 32 };
	DAMAC_STONES_WHITE = (SDL_Rect){ .x = 64, .y = 0, .w = 32, .h = 32 };

	DAMAC_STONES_BLACK_QUEEN = (SDL_Rect){ .x = 0, .y = 32, .w = 32, .h = 32 };
	DAMAC_STONES_WHITE_QUEEN = (SDL_Rect){ .x = 64, .y = 32, .w = 32, .h = 32 };

	DAMAC_SELECTION_BLUE = (SDL_Rect){ .x = 0, .y = 0, .w = 32, .h = 32 };
	DAMAC_SELECTION_RED = (SDL_Rect){ .x = 32, .y = 0, .w = 32, .h = 32 };

	return 1;
}

void player_select_piece(Game* game) 
{
	if (game->round % 2 == 0) 
	{
		Piece* piece = get_piece(game->board, game->white_player->x, game->white_player->y);

		if (piece != NULL && piece->color == White) 
		{
			game->selected_piece = piece;
			set_selectable_places(game);

			if (game->place_selected_length > 0) 
			{
				game->input_mode = SelectingPieceMove;
			}
		}
	}
	else 
	{
		Piece* piece = get_piece(game->board, game->black_player->x, game->black_player->y);

		if (piece != NULL && piece->color == Black) 
		{
			game->selected_piece = piece;
			set_selectable_places(game);

			if (game->place_selected_length > 0) 
			{
				game->input_mode = SelectingPieceMove;
			}
		}
	}
}

void escape_selection(Game* game) 
{
	game->input_mode = SelectingPiece;
	game->selected_piece = NULL;
}

void player_select_place(Game* game) 
{
	Place place = game->movable_places[game->place_selected_index];
	Piece* piece = get_piece(game->board, place.x, place.y);

	if (piece == NULL) 
	{
		move_piece(game->selected_piece, place.x, place.y);
		
		game->round += 1;
		game->input_mode = SelectingPiece;
		game->selected_piece = NULL;
	}
	else
	{
		eat_piece(game->board, game->selected_piece, piece);

		game->round += 1;
		game->input_mode = SelectingPiece;
		game->selected_piece = NULL;
	}
}

void set_selectable_places(Game* game) 
{
	Piece* piece;
	int index = 0;

	game->place_selected_length = 0;
	game->place_selected_index = 0;

	piece = get_piece(game->board, game->selected_piece->x + 1, game->selected_piece->y + 1);

	if (piece == NULL) 
	{
		if (can_move_piece(game->board, game->selected_piece, game->selected_piece->x + 1, game->selected_piece->y + 1)) 
		{
			game->movable_places[index].x = game->selected_piece->x + 1;
			game->movable_places[index].y = game->selected_piece->y + 1;

			game->place_selected_length += 1;

			index += 1;
		}
	}
	else 
	{
		if (can_eat_piece(game->board, game->selected_piece, piece)) 
		{
			game->movable_places[index].x = game->selected_piece->x + 1;
			game->movable_places[index].y = game->selected_piece->y + 1;

			game->place_selected_length += 1;

			index += 1;
		}
	}

	piece = get_piece(game->board, game->selected_piece->x - 1, game->selected_piece->y - 1);

	if (piece == NULL) 
	{
		if (can_move_piece(game->board, game->selected_piece, game->selected_piece->x - 1, game->selected_piece->y - 1)) 
		{
			game->movable_places[index].x = game->selected_piece->x - 1;
			game->movable_places[index].y = game->selected_piece->y - 1;

			game->place_selected_length += 1;

			index += 1;
		}
	}
	else 
	{
		if (can_eat_piece(game->board, game->selected_piece, piece)) 
		{
			game->movable_places[index].x = game->selected_piece->x - 1;
			game->movable_places[index].y = game->selected_piece->y - 1;

			game->place_selected_length += 1;

			index += 1;
		}
	}

	piece = get_piece(game->board, game->selected_piece->x + 1, game->selected_piece->y - 1);

	if (piece == NULL) 
	{
		if (can_move_piece(game->board, game->selected_piece, game->selected_piece->x + 1, game->selected_piece->y - 1)) 
		{
			game->movable_places[index].x = game->selected_piece->x + 1;
			game->movable_places[index].y = game->selected_piece->y - 1;

			game->place_selected_length += 1;

			index += 1;
		}
	}
	else 
	{
		if (can_eat_piece(game->board, game->selected_piece, piece)) 
		{
			game->movable_places[index].x = game->selected_piece->x + 1;
			game->movable_places[index].y = game->selected_piece->y - 1;

			game->place_selected_length += 1;

			index += 1;
		}
	}


	piece = get_piece(game->board, game->selected_piece->x - 1, game->selected_piece->y + 1);

	if (piece == NULL) 
	{
		if (can_move_piece(game->board, game->selected_piece, game->selected_piece->x - 1, game->selected_piece->y + 1)) 
		{
			game->movable_places[index].x = game->selected_piece->x - 1;
			game->movable_places[index].y = game->selected_piece->y + 1;

			game->place_selected_length += 1;

			index += 1;
		}
	}
	else 
	{
		if (can_eat_piece(game->board, game->selected_piece, piece)) 
		{
			game->movable_places[index].x = game->selected_piece->x - 1;
			game->movable_places[index].y = game->selected_piece->y + 1;

			game->place_selected_length += 1;

			index += 1;
		}
	}
}

void move_selection_up(Game* game) 
{
	if (game->input_mode == SelectingPiece) 
	{
		if (game->round % 2 == 0) 
		{
			if (game->white_player->y - 1 >= 0) 
			{
				game->white_player->y -= 1;
			}
		}
		else 
		{
			if (game->black_player->y - 1 >= 0) 
			{
				game->black_player->y -= 1;
			}
		}
	}
	else if (game->input_mode == SelectingPieceMove) 
	{
		if (game->place_selected_index + 1 < game->place_selected_length) 
		{
			game->place_selected_index += 1;
		}
	}
}

void move_selection_down(Game* game) 
{
	if (game->input_mode == SelectingPiece) 
	{
		if (game->round % 2 == 0) 
		{
			if (game->white_player->y + 1 < DAMAC_BOARD_SIZE) 
			{
				game->white_player->y += 1;
			}
		}
		else 
		{
			if (game->black_player->y + 1 < DAMAC_BOARD_SIZE) 
			{
				game->black_player->y += 1;
			}
		}
	}
	else if (game->input_mode == SelectingPieceMove) 
	{
		if (game->place_selected_index - 1 >= 0) 
		{
			game->place_selected_index -= 1;
		}
	}
}

void move_selection_left(Game* game) 
{
	if (game->input_mode == SelectingPiece) 
	{
		if (game->round % 2 == 0) 
		{
			if (game->white_player->x - 1 >= 0) 
			{
				game->white_player->x -= 1;
			}
		}
		else 
		{
			if (game->black_player->x - 1 >= 0) 
			{
				game->black_player->x -= 1;
			}
		}
	}
	else if (game->input_mode == SelectingPieceMove) 
	{
		if (game->place_selected_index - 1 >= 0) 
		{
			game->place_selected_index -= 1;
		}
	}
}

void move_selection_right(Game* game) 
{
	if (game->input_mode == SelectingPiece) 
	{
		if (game->round % 2 == 0) 
		{
			if (game->white_player->x + 1 < DAMAC_BOARD_SIZE) 
			{
				game->white_player->x += 1;
			}
		}
		else 
		{
			if (game->black_player->x + 1 < DAMAC_BOARD_SIZE) 
			{
				game->black_player->x += 1;
			}
		}
	}
	else if (game->input_mode == SelectingPieceMove) 
	{
		if (game->place_selected_index + 1 < game->place_selected_length) 
		{
			game->place_selected_index += 1;
		}
	}
}

void clean_game(Game* game) 
{
	SDL_FreeSurface(DAMAC_WOOD_SPREADSHEET);
	SDL_FreeSurface(DAMAC_STONES_SPREADSHEET);
	SDL_FreeSurface(DAMAC_SELECTION_SPREADSHEET);
 
	SDL_Quit();
}